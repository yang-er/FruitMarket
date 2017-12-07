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
/// ɨ�� 0001-9999 �����֡�
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
		printf("�����ʽ������ȷ�������Ƿ���0001-9999�ķ�Χ�ڡ�\n");
		ScanShort(message, i);
	}
}

/// <summary>
/// ɨ��32λ���Ρ�
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
		printf("�����ʽ�����޷�ʶ��Ϊ������\n");
		FlushStream();
		ScanInt(message, i);
	}
}

/// <summary>
/// ɨ��lenΪ���ȵ��ַ�������buffer��
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
/// ɨ��a-e����1-2����ASCII��ѡ��
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
		printf("�����ʽ���������Сд��ǰ��ո�\n");
		ScanOption(message, min, max, c);
	}
}

#define isTrue(c) ((c=='y')||(c=='Y'))
#define isFalse(c) ((c=='n')||(c=='N'))

/// <summary>
/// ɨ���� / ��ѡ�
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
		printf("�����ʽ���������Ƿ�Ϊy/Y/n/N��\n");
		return ScanBoolean(message);
	}
	else
	{
		return isTrue(c);
	}
}
