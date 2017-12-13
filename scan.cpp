#include "stdafx.h"
#include "scan.h"

#ifdef _MSC_VER
#if _MSC_VER==1200
#define FlushStream() fflush(stdin)
#elif _MSC_VER>1200
#define FlushStream() rewind(stdin)
#else
#define FlushStream() char cp = '\0'; while (cp != '\n' && cp != EOF) cp = getchar();
#endif
#else
#define FlushStream() rewind(stdin)
#endif

int scanf_result = 0;

void ScanShort(const char* message, short *i)
{
	printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf_result = scanf("%hd", i);
#else
	scanf_result = scanf_s("%hd", i);
#endif
	FlushStream();
	if (scanf_result != 1 || *i < 1 || *i > 9999)
	{
		printf("输入格式有误！请确认数字是否在0001-9999的范围内。\n");
		ScanShort(message, i);
	}
}

void ScanInt(const char* message, int *i)
{
	printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf_result = scanf("%d", i);
#else
	scanf_result = scanf_s("%d", i);
#endif
	FlushStream();
	if (scanf_result != 1)
	{
		printf("输入格式有误！无法识别为整数。\n");
		FlushStream();
		ScanInt(message, i);
	}
}

void ScanDouble(const char* message, double *i)
{
	printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf_result = scanf("%lf", i);
#else
	scanf_result = scanf_s("%lf", i);
#endif
	FlushStream();
	if (scanf_result != 1)
	{
		printf("输入格式有误！无法识别为浮点。\n");
		FlushStream();
		ScanDouble(message, i);
	}
}

void ScanText(const char* message, char *buffer, size_t len)
{
	memset(buffer, 0x00, sizeof(char) * len);
	printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf("%s", buffer);
#else
	scanf_s("%s", buffer, len);
#endif
	FlushStream();
	if (buffer[0] == '\0')
		ScanText(message, buffer, len);
}

void ScanOption(const char* message, const char min, const char max, char *c)
{
	printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf_result = scanf("%c", c);
#else
	scanf_result = scanf_s("%c", c);
#endif
	FlushStream();
	if (scanf_result != 1 || *c > max || *c < min)
	{
		printf("输入格式有误！请检查大小写和前后空格。\n");
		ScanOption(message, min, max, c);
	}
}

#define isTrue(c) ((c=='y')||(c=='Y'))
#define isFalse(c) ((c=='n')||(c=='N'))

bool ScanBoolean(const char* message)
{
	printf(message);
	char c;
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf_result = scanf("%c", &c);
#else
	scanf_result = scanf_s("%c", &c);
#endif
	FlushStream();
	if (scanf_result != 1 || !(isTrue(c) ^ isFalse(c)))
	{
		printf("输入格式有误！请检查是否为y/Y/n/N。\n");
		return ScanBoolean(message);
	}
	else
	{
		return isTrue(c);
	}
}
