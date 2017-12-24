#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "user.h"

user *pUserFront = NULL;
user *pUserRear = NULL;
user *pUserTemp = NULL;

const char *pfUser = "user.dat";

void LoadUserFromFile()
{
	// 清空内存中的用户
	while (pUserFront != NULL)
	{
		pUserTemp = pUserFront;
		pUserFront = pUserFront->next;
		pUserTemp->next = NULL;
		_free(pUserTemp, user);
	}
	pUserRear = NULL;
	pUserTemp = NULL;

	FILE* pFile = NULL;
	int count = OpenFile(&pFile, pfUser, sizeof(user));

	// 无数据的时候初始化为空数组
	if (count == 0)
	{
		_alloc(pUserTemp, user);
		strcpy(pUserTemp->name, "现金");
		pUserTemp->uid = -1;
		pUserFront = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
		return;
	}

	// 有数据则读取
	for (int i = 0; i < count; i++)
	{
		_alloc(pUserTemp, user);
		fread(pUserTemp, sizeof(user), 1, pFile);
		if (pUserFront == NULL) pUserFront = pUserTemp;
		if (pUserRear != NULL) pUserRear->next = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
	}
	fclose(pFile);

	pUserFront->balance = 0;
	pUserFront->todayUsage = 0;
}

bool SaveUserToFile()
{
	FILE *pFile;
	do {
		pFile = fopen(pfUser, "w+");
	} while (pFile == NULL && ScanBoolean("文件user.dat无法打开，是否重试？(y/n)："));

	if (pFile == NULL)
	{
		printf("放弃文件保存，所做更改将不被保存. . . \n");
		while (pUserFront != NULL)
		{
			pUserTemp = pUserFront;
			pUserFront = pUserFront->next;
			pUserTemp->next = NULL;
			_free(pUserTemp, ticket);
		}
		pUserRear = NULL;
		pUserTemp = NULL;
		return false;
	}

	while (pUserFront != NULL)
	{
		pUserTemp = pUserFront;
		pUserFront = pUserFront->next;
		pUserTemp->next = NULL;
		fwrite(pUserTemp, sizeof(user), 1, pFile);
		_free(pUserTemp, user);
	}
	pUserRear = NULL;
	pUserTemp = NULL;
	fclose(pFile);
	return true;
}

bool ChargeToCard(short uid, int credit, bool isAdd)
{
	if(pUserTemp == NULL || pUserTemp->uid != uid)
		pUserTemp = GetCardById(uid);

	if (isAdd)
	{
		if (pUserTemp->balance + credit > 1000000 || pUserTemp->balance + credit < 0)
		{
			printf("余额超过限制，充值失败。\n");
			return false;
		}
		else
		{
			pUserTemp->balance += credit;
			return true;
		}
	}
	else
	{
		if (pUserTemp->balance < credit && uid != -1)
		{
			printf("余额不足，无法用会员卡消费。\n");
			return false;
		}
		else
		{
			pUserTemp->balance -= credit;
			pUserTemp->todayUsage += credit;
			return true;
		}
	}
	
}

void CreateCard()
{
	do {
		_alloc(pUserTemp, user);

		// 输入并检测卡号
		ScanShort("请输入卡号：", &pUserTemp->uid, false);
		if (GetCardById(pUserTemp->uid) != NULL)
		{
			printf("会员卡%04d已存在！\n", pUserTemp->uid);
			_free(pUserTemp, user);
			pUserTemp = NULL;
			continue;
		}
		ScanText("请输入持卡人姓名：", pUserTemp->name, 21);

		// 输入并检测余额情况
		double money;
		ScanDouble("请输入会员卡余额：", &money);
		pUserTemp->balance = cent(money);
		if (pUserTemp->balance > 1000000 || pUserTemp->balance < 0)
		{
			printf("余额超过限制，建卡失败。\n");
			_free(pUserTemp, user);
			pUserTemp = NULL;
			continue;
		}

		// 入队列
		pUserRear->next = pUserTemp;
		pUserRear = pUserRear->next;
		pUserTemp = NULL;

		// 检测是否继续
	} while (ScanBoolean("是否继续输入？(y/n)："));
}

user *GetCardById(short uid)
{
	user* temp;
	temp = pUserFront;
	while (temp != NULL && temp->uid != uid)
		temp = temp->next;
	return temp;
}

bool CrashCard()
{
	short i;
	ScanShort("请输入会员卡号：", &i, false);
	if (!ScanBoolean("确定要删除这个会员吗？(y/n)："))
		return false;
	pUserTemp = pUserFront;
	while (pUserTemp->next != NULL && pUserTemp->next->uid != i)
		pUserTemp = pUserTemp->next;
	if (pUserTemp->next == NULL)
	{
		printf("用户%04hd不存在！\n", i);
		pUserTemp = NULL;
		return false;
	}
	else
	{
		user *temp = pUserTemp->next;
		pUserTemp->next = temp->next;
		if (pUserTemp->next == NULL) pUserRear = pUserTemp;
		_free(temp, user);
		pUserTemp = NULL;
		return true;
	}
}

bool ListVip(user* current)
{
	printf("|\n");
	printf("|  姓名：%s\n", current->name);
	printf("|  卡号：%04hd\n", current->uid);
	printf("|  余额：%.2lf\n", dollar(current->balance));
	printf("|  已用：%.2lf\n", dollar(current->todayUsage));
	printf("|\n");
	printf("==================\n");
	return false;
}

void ListAllVips()
{
	flush_data();
	printf("==================\n");
	printf("|    会员信息\n");
	printf("==================\n");
	pUserTemp = pUserFront->next;
	while (pUserTemp != NULL)
	{
		ListVip(pUserTemp);
		pUserTemp = pUserTemp->next;
	}
}

bool ChangeVip(short uid) {
	pUserTemp = GetCardById(uid);
	if (pUserTemp == NULL)
	{
		printf("用户%04hd不存在！\n", uid);
		return false;
	}
	if (ScanBoolean("是否修改会员姓名？(y/n)："))
	{
		ScanText("新名称：", pUserTemp->name, 21);
	}
	pUserTemp = NULL;
	return true;
}

void PrintVip()
{
	flush_data();
	short uid;
	ScanShort("请输入会员卡号：", &uid, true);
	pUserTemp = GetCardById(uid);
	if (pUserTemp == NULL)
	{
		printf("没有找到该会员。\n");
	}
	else
	{
		printf("==================\n");
		ListVip(pUserTemp);
		pUserTemp = NULL;
	}
}

void ChargeInConsole(short uid)
{
	double money;
	int credit;

	if (uid == -2)
	{
		// 输入会员卡号
		ScanShort("请输入会员卡号：", &uid, false);
		pUserTemp = GetCardById(uid);
		if (pUserTemp == NULL)
		{
			printf("用户%04hd不存在！\n", uid);
			sleep(500);
			return;
		}
	}

	// 输入充值金额
	ScanDouble("请输入充值金额：", &money);
	if (money <= 0 || money > 1000)
	{
		printf("充值失败，请检查您输入的金额。\n");
		sleep(500);
	}
	else
	{
		credit = cent(money);
		if (ChargeToCard(uid, credit, true))
			printf("充值成功。\n");
	}
}

void menu_user()
{
	clear();
	char op;
	short i1;
	while (true)
	{
		printf("==================\n");
		printf("|    用户系统\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.办理会员\n");
		printf("|   2.会员充值\n");
		printf("|   3.修改信息\n");
		printf("|   4.删除会员\n");
		printf("|   5.查询会员\n");
		printf("|   6.列出会员\n");
		printf("|   7.退出\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("请选择进入：", '1', '7');
		printf("\n");
		switch (op)
		{
			case '1': CreateCard(); break;
			case '2': ChargeInConsole(-2); break;
			case '3': ScanShort("请输入会员卡号：", &i1, false); ChangeVip(i1); printf("修改结束。\n"); break;
			case '4': if(CrashCard()) printf("删除卡成功。\n"); break;
			case '5': PrintVip(); _pause(); break;
			case '6': ListAllVips(); _pause(); break;
			case '7': if (ScanBoolean("确定退出吗？(y/n)：")) op = -52; break;
			default: break;
		}
		if (op == -52)
		{
			SaveUserToFile();
			LoadUserFromFile();
			sleep(500);
			clear();
			break;
		}
		sleep(500);
		clear();
	}
}
