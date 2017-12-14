#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"
#include "structs.h"

user *pUserFront = NULL;
user *pUserRear = NULL;
user *pUserTemp = NULL;
const char *pfUser = "user.dat";

void LoadUserFromFile()
{
	struct stat pStat;
	stat(pfUser, &pStat);

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

	// 文件不存在的时候初始化为空数组
	if (stat(pfUser, &pStat) == -1)
	{
		_alloc(pUserTemp, user);
		strcpy(pUserTemp->name, "现金");
		pUserTemp->uid = -1;
		pUserFront = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
		return;
	}

	// 检测文件完整度
	if (pStat.st_size % sizeof(user) != 0)
		DataNotFulfilled(NULL, pfUser);

	// 打开文件
	FILE *pFile = fopen(pfUser, "r");
	CheckFile(pFile, pfUser);
	for (int i = 0; i < pStat.st_size / sizeof(user); i++)
	{
		_alloc(pUserTemp, user);
		fread(pUserTemp, sizeof(user), 1, pFile);
		if (*((char*)pUserTemp) == -1)
			printf("gg");
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
	FILE *pFile = fopen(pfUser, "w+");
	CheckFile(pFile, pfUser);
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
		if (pUserTemp->balance + credit > 1000000)
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
		ScanShort("请输入卡号：", &pUserTemp->uid);
		if (GetCardById(pUserTemp->uid) != NULL)
		{
			printf("会员卡%04d已存在！\n", pUserTemp->uid);
			_free(pUserTemp, user);
			pUserTemp = NULL;
			continue;
		}
		ScanText("请输入持卡人姓名：", pUserTemp->name, 21);
		double money;
		ScanDouble("请输入会员卡余额：", &money);
		pUserTemp->balance = (int)floor(money * 100 + 0.5);
		pUserRear->next = pUserTemp;
		pUserRear = pUserRear->next;
		pUserTemp = NULL;
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
	ScanShort("请输入会员卡号:", &i);
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
	printf("|  余额：%d.%02d\n", current->balance / 100, current->balance % 100);
	printf("|  已用：%d.%02d\n", current->todayUsage / 100, current->todayUsage % 100);
	printf("|\n");
	printf("==================\n");
	return false;
}

void ListAllVips()
{
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
		ScanText("新名称：", pUserTemp->name, 20);
	}
	return true;
}

void _user()
{
	clear();
	char op;
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
		case '1':
			CreateCard();
			sleep(500);
			break;
		case '5':
			// 打印单个会员
			{
				short i;
				ScanShort("请输入会员卡号：", &i);
				pUserTemp = GetCardById(i);
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
				pause();
			}
			break;
		case '6':
			// 打印所有会员
			ListAllVips();
			pause();
			break;
		case '4':
			if(CrashCard())
				printf("删除卡成功。\n");
			sleep(500);
			break;
		case '7':
			if (ScanBoolean("确定退出嘛(y/n)："))
				op = -52;
			break;
		case '2':
			// 单个卡充值
			{
				short j;
				double m;
				int n;
				ScanShort("请输入会员卡号：", &j);
				if (pUserTemp == NULL)
				{
					printf("用户%04hd不存在！\n", j);
					sleep(500);
					break;
				}
				ScanDouble("请输入充值金额：", &m);
				if (m <= 0 || m > 1000)
				{
					printf("充值失败，请检查您输入的金额。\n");
					sleep(500);
				}
				else
				{
					n = (int)floor(m * 100 + 0.5);
					if (ChargeToCard(j, (int)floor(m * 100 + 0.5), true))
						printf("充值成功。\n");
				}
				sleep(500);
			}
			break;
		case '3':
			short i1;
			ScanShort("请输入会员卡号:", &i1);
			ChangeVip(i1);
			printf("修改结束。\n");
			sleep(500);
			break;
		default:
			break;
		}
		if (op == -52)
		{
			SaveUserToFile();
			LoadUserFromFile();
			sleep(500);
			clear();
			break;
		}
		clear();
	}
}
