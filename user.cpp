#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"
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
	return false;
}

void CreateCard()
{
	do {
		pUserTemp = (struct user *)malloc(sizeof(struct user));
		memset(pUserTemp, 0x00, sizeof(struct user));
		ScanText("请输入持卡人签名:", pUserTemp->name, 21);
		ScanShort("请输入编号:", &pUserTemp->uid);
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
	ScanShort("请输入会员卡号", &i);
	while (pUserFront != NULL && pUserFront->uid == i)

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
	printf("1.创建单个会员并保存 2.加载会员信息 3.加载单个会员 4.加载全部会员 5.删除单个会员 6.退出\n");
	ScanOption("请选择进入：", '1', '6', &op);
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
		do {
			pUserTemp = pUserFront;
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
	default:
		break;
}
if (op == -52)
break;
	}
}
