#include "stdafx.h"
#include "scan.h"

static int scanf_result = 0;
time_t pTime = 0;
struct tm *pCurrentDate = NULL;

void ScanShort(const char* message, short *i)
{
	printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
	scanf_result = scanf("%hd", i);
#else
	scanf_result = scanf_s("%hd", i);
#endif
	flush();
	if (scanf_result != 1 || *i < 1 || *i > 9999)
	{
		printf("�����ʽ������ȷ�������Ƿ���0001-9999�ķ�Χ�ڡ�\n");
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
	flush();
	if (scanf_result != 1)
	{
		printf("�����ʽ�����޷�ʶ��Ϊ������\n");
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
	flush();
	if (scanf_result != 1)
	{
		printf("�����ʽ�����޷�ʶ��Ϊ���㡣\n");
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
	flush();
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
	flush();
	if (scanf_result != 1 || *c > max || *c < min)
	{
		printf("�����ʽ���������Сд��ǰ��ո�\n");
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
	flush();
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

void CheckFile(FILE* pFile, const char* pszName)
{
	if (pFile == NULL)
	{
		fprintf(stderr, "�ļ�%s��ʧ�ܣ��˳��С���", pszName);
		exit(4);
	}
}

void DataNotFulfilled(FILE* pFile, const char* pszName)
{
	fprintf(stderr, "%s�ļ����ݱ��ƻ����޷�У��ͨ����", pszName);
	exit(4);
}

time_t ScanTime(const char* message)
{
	int dHour, dMinute;
	while (true)
	{
		printf(message);
#ifdef _CRT_SECURE_NO_WARNINGS
		scanf_result = scanf("%d:%d", &dHour, &dMinute);
#else
		scanf_result = scanf_s("%d:%d", &dHour, &dMinute);
#endif
		flush();
		if (scanf_result != 2 ||
			dHour > 23 || dHour < 0 || dMinute > 59 || dMinute < 0)
		{
			printf("����ʱ���ʽ���󣡸�ʽ��HH:MM����23:59��\n");
			continue;
		}
		break;
	}
	return pTime + dMinute * 60 + dHour * 3600;
}

void SetCurrentDate()
{
	// ��ȡϵͳʱ��
	time(&pTime);
	pCurrentDate = localtime(&pTime);
	printf("ϵͳ���ڣ�%d��%d��%d�ա�\n",
		1900 + pCurrentDate->tm_year,
		pCurrentDate->tm_mon + 1,
		pCurrentDate->tm_mday);
	pCurrentDate->tm_hour = 0;
	pCurrentDate->tm_min = 0;
	pCurrentDate->tm_sec = 0;

	// �Ƿ�ʹ�õ�ǰʱ��
	if (!ScanBoolean("�Ƿ�ʹ�õ�ǰ���ڣ�(y/n)��"))
	{
		while (true)
		{
			flush();
			printf("�����뵱ǰ����(YYYY-MM-DD)��");
#ifdef _CRT_SECURE_NO_WARNINGS
			scanf_result = scanf("%d-%d-%d", &pCurrentDate->tm_year, &pCurrentDate->tm_mon, &pCurrentDate->tm_mday);
#else
			scanf_result = scanf_s("%d-%d-%d", &pCurrentDate->tm_year, &pCurrentDate->tm_mon, &pCurrentDate->tm_mday);
#endif
			flush();
			if (scanf_result != 3)
			{
				printf("�����ʽ���󣡸�ʽ��YYYY-MM-DD����2017-12-21��\n");
				continue;
			}
			pCurrentDate->tm_year -= 1900;
			pCurrentDate->tm_mon -= 1;
			
			pTime = mktime(pCurrentDate);
			if (pTime == -1)
			{
				printf("���������޷���ʶ��\n");
				continue;
			}
			break;
		}

		// �ٴ����ʱ��
		printf("�������ڣ�%d��%d��%d�ա�\n",
			1900 + pCurrentDate->tm_year,
			pCurrentDate->tm_mon + 1,
			pCurrentDate->tm_mday);
	}
	else
	{
		pTime = mktime(pCurrentDate);
	}
}
