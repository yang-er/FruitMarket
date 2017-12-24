#include "stdafx.h"
#include "scan.h"

static int scanf_result = 0;
time_t pTime = 0;
struct tm pDate;
static char chOB[10];
static struct stat pStat;

void ScanShort(const char* message, short *i, bool canFF)
{
	do {
		printf(message);
		scanf_result = scanf("%hd", i);
		fgets(chOB, 10, stdin);
		trim(chOB, 10);
		if (*chOB != 0) scanf_result++;
		flush();
	} while (
		(scanf_result != 1 || ((*i < 1 || *i > 9999) && !(canFF && *i == -1))) // ����Ƿ�����ɹ�
		&& printf("�����ʽ������ȷ�������Ƿ���0001-9999�ķ�Χ�ڡ�\n") // ���ɹ�ʱ���������ʾ
	);
}

void ScanInt(const char* message, int *i)
{
	do {
		printf(message);
		scanf_result = scanf("%d", i);
		fgets(chOB, 10, stdin);
		trim(chOB, 10);
		if (*chOB != 0) scanf_result++;
		flush();
	} while (
		(scanf_result != 1) // ����Ƿ�����ɹ�
		&& printf("�����ʽ�����޷�ʶ��Ϊ������\n") // ���ɹ�ʱ���������ʾ
	);
}

void ScanDouble(const char* message, double *i)
{
	do {
		printf(message);
		scanf_result = scanf("%lf", i);
		fgets(chOB, 10, stdin);
		trim(chOB, 10);
		if (*chOB != 0) scanf_result++;
		flush();
	} while (
		(scanf_result != 1) // ����Ƿ�����ɹ�
		&& printf("�����ʽ�����޷�ʶ��Ϊ���㡣\n") // ���ɹ�ʱ���������ʾ
	);
}

void ScanText(const char* message, char *buffer, size_t len)
{
	do {
		memset(buffer, 0x00, sizeof(char) * len);
		printf(message);
		scanf("%20s", buffer);
		flush();
		// trim(buffer, len);
	} while (
		(buffer[0] == '\0') // ����Ƿ�����ɹ�
		&& printf("����ַ�������Ϊ�գ�\n") // ���ɹ�ʱ���������ʾ
	);
}

char ScanOption(const char* message, const char min, const char max)
{
	do {
		printf(message);
		memset(chOB, 0x00, 10);
		fgets(chOB, 9, stdin);
		flush();
		trim(chOB, 10);
	} while (
		(strlen(chOB) != 1 || chOB[0] < min || chOB[0] > max) // ����Ƿ�����ɹ�
		&& printf("�����ʽ���������Сд��ǰ���ַ���\n") // ���ɹ�ʱ���������ʾ
	);
	return chOB[0];
}

#define isTrue(c) ((c=='y')||(c=='Y'))
#define isFalse(c) ((c=='n')||(c=='N'))

bool ScanBoolean(const char* message)
{
	do {
		printf(message);
		memset(chOB, 0x00, 10);
		fgets(chOB, 9, stdin);
		flush();
		trim(chOB, 10);
	} while (
		(strlen(chOB) != 1 || !(isTrue(chOB[0]) ^ isFalse(chOB[0]))) // ����Ƿ�����ɹ�
		&& printf("�����ʽ���������Ƿ�Ϊy/Y/n/N��\n") // ���ɹ�ʱ���������ʾ
	);
	return isTrue(chOB[0]);
}

int OpenFile(FILE* *pFile, const char* pszName, size_t dwStruct)
{
	if (stat(pszName, &pStat) == -1)
	{
		fprintf(stderr, "�ļ�%s�����ڣ�Ĭ�����ݽ�����Ϊ��. . . \n", pszName);
		return 0;
	}

	if (pStat.st_size % dwStruct != 0)
	{
		fprintf(stderr, "%s�ļ����ݱ��ƻ����޷�У��ͨ�����˳���. . . \n", pszName);
		sleep(5000);
		exit(4);
	}

	*pFile = fopen(pszName, "r");
	if (*pFile == NULL)
	{
		fprintf(stderr, "�ļ�%s��ʧ�ܣ��˳���. . . \n", pszName);
		sleep(5000);
		exit(4);
	}

	if (pStat.st_size == 0)
	{
		fclose(*pFile);
		*pFile = NULL;
	}

	return (int)(pStat.st_size / dwStruct);
}

time_t ScanTime(const char* message)
{
	int dHour, dMinute;
	do {
		printf(message);
		scanf_result = scanf("%d:%d", &dHour, &dMinute);
		flush();
	} while (
		(scanf_result != 2 || dHour > 23 || dHour < 0 || dMinute > 59 || dMinute < 0) // ����Ƿ�����ɹ�
		&& printf("����ʱ���ʽ���󣡸�ʽ��HH:MM����23:59��\n") // ���ɹ�ʱ���������ʾ
	);
	return pTime + dMinute * 60 + dHour * 3600;
}

void SetCurrentDate()
{
	// ��ȡϵͳʱ��
	time(&pTime);
	LocalTime(&pDate, &pTime);
	printf("ϵͳ���ڣ�%d��%d��%d�ա�\n",
		1900 + pDate.tm_year,
		pDate.tm_mon + 1,
		pDate.tm_mday);
	pDate.tm_hour = 0;
	pDate.tm_min = 0;
	pDate.tm_sec = 0;

	// �Ƿ�ʹ�õ�ǰʱ��
	if (!ScanBoolean("�Ƿ�ʹ�õ�ǰ���ڣ�(y/n)��"))
	{
		do {
			printf("�����뵱ǰ����(YYYY-MM-DD)��");
			scanf_result = scanf("%d-%d-%d", &pDate.tm_year, &pDate.tm_mon, &pDate.tm_mday);
			flush();

			// ����Ƿ�����ɹ�
			if (scanf_result != 3) continue;
			
			pDate.tm_year -= 1900;
			pDate.tm_mon -= 1;
			
			pTime = mktime(&pDate);
		} while (
			((scanf_result != 3) && printf("�����ʽ���󣡸�ʽ��YYYY-MM-DD����2017-12-21��\n")) // ���벻�������ܱ�ʶ��
			|| ((pTime == -1) && printf("���������޷���ʶ��\n")) // ���ݲ��ܱ�ʶ��
		);

	}
	else
	{
		pTime = mktime(&pDate);
	}
}

#define isspace(c) ((c>=0&&c<=' ')||c==0x7f)

void trim(char *buf, size_t len)
{
	// �½�������
	char *tmp = (char*) malloc(len), *head = tmp, *tail = tmp;
	memcpy(tmp, buf, len);

	// ��ͷ���������ַ�
	if (*head && isspace(*head)) *head++ = '\0';

	// ����ַ����Ƿ�ʣ��
	if (*head == '\0')
	{
		memset(buf, 0x00, len);
		memset(tmp, 0x00, len);
		free(tmp);
		return;
	}

	// ��β�����������ַ�
	tail = head + strlen(head) - 1;
	while (tail >= head && isspace(*tail)) *tail-- = '\0';

	// �������յ��ַ���
	memset(buf, 0x00, len);
	memcpy(buf, head, tail - head + 1);
	memset(tmp, 0x00, len);
	free(tmp);
}
