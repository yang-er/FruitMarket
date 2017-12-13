#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"
#include "structs.h"
#include <sys/stat.h>

struct user *pUserFront = NULL;
struct user *pUserRear = NULL;
struct user *pUserTemp = NULL;
const char *pfUser = "user.dat";

void LoadUserFromFile()
{
	struct stat pStat;
	stat(pfUser, &pStat);

	// 文件不存在的时候初始化为空数组
	if (stat(pfUser, &pStat) == -1)
	{
		pUserTemp = (struct user*) malloc(sizeof(struct user));
		memset(pUserTemp, 0x00, sizeof(struct user));
		strcpy(pUserTemp->name, "现金");
		pUserTemp->uid = -1;
		pUserFront = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
		return;
	}

	// 检测文件完整度
	if (pStat.st_size % sizeof(struct user) != 0)
		DataNotFulfilled(NULL, pfUser);

	// 打开文件
	FILE *pFile = fopen(pfUser, "r");
	CheckFile(pFile, pfUser);
	for (int i = 0; i < pStat.st_size / sizeof(struct user); i++)
	{
		pUserTemp = (struct user*) malloc(sizeof(struct user));
		memset(pUserTemp, 0x00, sizeof(struct user));
		fread(pUserTemp, sizeof(struct user), 1, pFile);
		if (*((char*)pUserTemp) == -1)
			printf("gg");
		if (pUserFront == NULL) pUserFront = pUserTemp;
		if (pUserRear != NULL) pUserRear->next = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
	}
	fclose(pFile);

}

bool SaveUserToFile()
{
	FILE *pFile = fopen(pfUser, "w+");
	CheckFile(pFile, pfUser);
	while (pUserFront != NULL)
	{
		pUserTemp = pUserFront;
		pUserFront = pUserFront->next;
		pUserTemp->next = NULL;
		fwrite(pUserTemp, sizeof(struct user), 1, pFile);
		free(pUserTemp);
	}
	pUserRear = NULL;
	pUserTemp = NULL;
	fclose(pFile);
	return true;
}

bool ChargeToCard(short uid, int credit, bool isAdd)
{
	pUserTemp = pUserFront;
	do {
		pUserTemp = pUserTemp->next;
	} while (pUserTemp != NULL && pUserTemp->uid != uid);
	if (pUserTemp == NULL)
	{
		printf("没有找到\n");
		return false;
	}
	if (isAdd) {
		if (pUserTemp->balance + credit > 1000000)
			printf("充值失败");
		else
			pUserTemp->balance = pUserTemp->balance + credit;
	}
	else
	{
		if (pUserTemp->balance - credit < 0)
			printf("余额不足,无法用会员卡消费");
		else
			pUserTemp->balance = pUserTemp->balance - credit;
	}
	return false;
}

void CreateCard()
{
	struct user *q;
	do {
		pUserTemp = (struct user *)malloc(sizeof(struct user));
		memset(pUserTemp, 0x00, sizeof(struct user));
		ScanText("请输入持卡人签名:", pUserTemp->name, 21);
		ScanShort("请输入编号:", &pUserTemp->uid);
			q = pUserFront;
				do {
					q = q->next;
				} while (q != NULL && q->uid != pUserTemp->uid);
				if (q != NULL)
				{
					printf("会员已存在,请重新输入\n");
					ScanShort("请输入编号:", &pUserTemp->uid);
				}
		double money;
		ScanDouble("请输入会员卡余额:", &money);
		pUserTemp->balance = (int)floor(money * 100 + 0.5);
		pUserRear->next = pUserTemp;
		pUserRear = pUserRear->next;
		pUserTemp = NULL;
	} while (ScanBoolean("是否继续输入？(y/n)："));
}

bool CrashCard()
{
	short i;
	ScanShort("请输入会员卡号:", &i);
	pUserTemp = pUserFront;
	while (pUserTemp != NULL && pUserTemp->uid == i)
		pUserTemp = pUserTemp->next;
	struct user *q = NULL, *p =pUserTemp;
	while (p != NULL)
	{
		if (p->uid == i)
			q->next = p->next;

		else
			q = p;
		p = p->next;
	}
	return false;
}

bool ListVip(struct user* current)
{
	printf("==================\n");
	printf("|    会员信息\n");
	printf("==================\n");
	printf("\n");
	printf("会员姓名:%s\n", current->name);
	printf("会员卡号:%04hd\n", current->uid);
	printf("用户余额:%d.%02d\n", current->balance / 100, current->balance % 100);
	printf("今日开销:%d\n", current->todayUsage);
	return false;
}

void ListAllVips()
{
	pUserTemp = pUserFront->next;
	while (pUserTemp != NULL)
	{
		ListVip(pUserTemp);
		pUserTemp = pUserTemp->next;
	}
}

void _user_test()
{
	ClearScreen();
	char op;
	while (1)
	{
	printf("1.创建单个会员 2.加载会员信息 3.加载单个会员 4.加载全部会员 5.删除单个会员 6.退出 7.充值或消费\n");
	ScanOption("请选择进入：", '1', '7', &op);
	switch (op)
	{
	case '1':
		CreateCard();
		break;
	case '2':
		LoadUserFromFile();
		break;
	case '3':
		short i;
		ScanShort("请输入会员卡号:", &i);
		pUserTemp = pUserFront;
		do {
			pUserTemp = pUserTemp->next;
		} while (pUserTemp != NULL && pUserTemp->uid != i);
		if (pUserTemp == NULL)
			printf("没有找到\n");
		else
			ListVip(pUserTemp);
		pUserTemp = NULL;
		break;
	case '4':
		ListAllVips();
		break;
	case '5':
		CrashCard();
		break;
	case '6':
		if (ScanBoolean("确定退出嘛(y/n)："))
			op = -52;
	case '7':
		short j;
		int k;
		double m;
		int n;
		ScanShort("请输入会员卡号(现金为'-1'):", &j);
		if (j == -1)
			break;
		bool isadd;
		ScanInt("请输入充值或消费,1.充值,0.消费", &k);
		if (k == 1)
			isadd = true;
		if (k == 0)
			isadd = false;
		ScanDouble("请输入充值金额:", &m);
		if (m <= 0 || m > 1000)
			printf("充值失败");
		else {
			n = (int)floor(m * 100 + 0.5);
			ChargeToCard(j, n, isadd);
		}
		break;
	default:
		break;
}
if (op == -52)
break;
	}
}
