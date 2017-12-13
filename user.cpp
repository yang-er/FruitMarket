#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"

struct user _defalut_user = { "现金", -1, 0, 0, NULL };
struct user *pUserFront = &_defalut_user;
struct user *pUserRear = &_defalut_user;
struct user *pUserTemp = NULL;
const char *pfUser = "user.dat";


void LoadUserFromFile()
{
	
	return;
}

bool SaveUserToFile()
{
	FILE *pFile;
	pFile = fopen(pfUser, "w+");
	CheckFile(pFile, pfUser);
	
	return false;
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
