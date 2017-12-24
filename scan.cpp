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
		(scanf_result != 1 || ((*i < 1 || *i > 9999) && !(canFF && *i == -1))) // 检测是否输入成功
		&& printf("输入格式有误！请确认数字是否在0001-9999的范围内。\n") // 不成功时输出错误提示
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
		(scanf_result != 1) // 检测是否输入成功
		&& printf("输入格式有误！无法识别为整数。\n") // 不成功时输出错误提示
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
		(scanf_result != 1) // 检测是否输入成功
		&& printf("输入格式有误！无法识别为浮点。\n") // 不成功时输出错误提示
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
		(buffer[0] == '\0') // 检测是否输入成功
		&& printf("输出字符串不能为空！\n") // 不成功时输出错误提示
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
		(strlen(chOB) != 1 || chOB[0] < min || chOB[0] > max) // 检测是否输入成功
		&& printf("输入格式有误！请检查大小写和前后字符。\n") // 不成功时输出错误提示
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
		(strlen(chOB) != 1 || !(isTrue(chOB[0]) ^ isFalse(chOB[0]))) // 检测是否输入成功
		&& printf("输入格式有误！请检查是否为y/Y/n/N。\n") // 不成功时输出错误提示
	);
	return isTrue(chOB[0]);
}

int OpenFile(FILE* *pFile, const char* pszName, size_t dwStruct)
{
	if (stat(pszName, &pStat) == -1)
	{
		fprintf(stderr, "文件%s不存在，默认数据将设置为空. . . \n", pszName);
		return 0;
	}

	if (pStat.st_size % dwStruct != 0)
	{
		fprintf(stderr, "%s文件数据被破坏！无法校验通过，退出中. . . \n", pszName);
		sleep(5000);
		exit(4);
	}

	*pFile = fopen(pszName, "r");
	if (*pFile == NULL)
	{
		fprintf(stderr, "文件%s打开失败！退出中. . . \n", pszName);
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
		(scanf_result != 2 || dHour > 23 || dHour < 0 || dMinute > 59 || dMinute < 0) // 检测是否输入成功
		&& printf("输入时间格式有误！格式：HH:MM，如23:59。\n") // 不成功时输出错误提示
	);
	return pTime + dMinute * 60 + dHour * 3600;
}

void SetCurrentDate()
{
	// 获取系统时间
	time(&pTime);
	LocalTime(&pDate, &pTime);
	printf("系统日期：%d年%d月%d日。\n",
		1900 + pDate.tm_year,
		pDate.tm_mon + 1,
		pDate.tm_mday);
	pDate.tm_hour = 0;
	pDate.tm_min = 0;
	pDate.tm_sec = 0;

	// 是否使用当前时间
	if (!ScanBoolean("是否使用当前日期？(y/n)："))
	{
		do {
			printf("请输入当前日期(YYYY-MM-DD)：");
			scanf_result = scanf("%d-%d-%d", &pDate.tm_year, &pDate.tm_mon, &pDate.tm_mday);
			flush();

			// 检测是否输入成功
			if (scanf_result != 3) continue;
			
			pDate.tm_year -= 1900;
			pDate.tm_mon -= 1;
			
			pTime = mktime(&pDate);
		} while (
			((scanf_result != 3) && printf("输入格式有误！格式：YYYY-MM-DD，如2017-12-21。\n")) // 输入不完整不能被识别
			|| ((pTime == -1) && printf("输入内容无法被识别！\n")) // 内容不能被识别
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
	// 新建缓冲区
	char *tmp = (char*) malloc(len), *head = tmp, *tail = tmp;
	memcpy(tmp, buf, len);

	// 从头消除无用字符
	if (*head && isspace(*head)) *head++ = '\0';

	// 检测字符串是否剩余
	if (*head == '\0')
	{
		memset(buf, 0x00, len);
		memset(tmp, 0x00, len);
		free(tmp);
		return;
	}

	// 从尾部消除无用字符
	tail = head + strlen(head) - 1;
	while (tail >= head && isspace(*tail)) *tail-- = '\0';

	// 返回最终的字符串
	memset(buf, 0x00, len);
	memcpy(buf, head, tail - head + 1);
	memset(tmp, 0x00, len);
	free(tmp);
}
