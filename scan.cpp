#include "stdafx.h"

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

/// <summary>
/// 扫描 0001-9999 的数字。
/// </summary>
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

/// <summary>
/// 扫描32位整形。
/// </summary>
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

/// <summary>
/// 扫描len为长度的字符串进入buffer。
/// </summary>
void ScanText(const char* message, char *buffer, int len)
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

/// <summary>
/// 扫描a-e或者1-2连续ASCII的选项
/// </summary>
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

/// <summary>
/// 扫描是 / 否选项。
/// </summary>
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
