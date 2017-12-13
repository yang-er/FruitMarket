#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"

struct user _defalut_user = { "�ֽ�", -1, 0, 0, NULL };
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
		ScanText("������ֿ���ǩ��:", pUserTemp->name, 21);
		ScanShort("��������:", &pUserTemp->uid);
		double money;
		ScanDouble("�������Ա�����:", &money);
		pUserTemp->balance = (int)floor(money * 100 + 0.5);
		pUserRear->next = pUserTemp;
		pUserRear = pUserRear->next;
		pUserTemp = NULL;
	} while (ScanBoolean("�Ƿ�������룿(y/n)��"));
}

bool CrashCard()
{
	short i;
	ScanShort("�������Ա����", &i);
	while (pUserFront != NULL && pUserFront->uid == i)

	return false;
}

bool ListVip(struct user* current)
{
	printf("==================\n");
	printf("|    ��Ա��Ϣ\n");
	printf("==================\n");
	printf("\n");
	printf("��Ա����:%s\n", current->name);
	printf("��Ա����:%04hd\n", current->uid);
	printf("�û����:%d.%02d\n", current->balance / 100, current->balance % 100);
	printf("���տ���:%d\n", current->todayUsage);
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
	printf("1.����������Ա������ 2.���ػ�Ա��Ϣ 3.���ص�����Ա 4.����ȫ����Ա 5.ɾ��������Ա 6.�˳�\n");
	ScanOption("��ѡ����룺", '1', '6', &op);
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
		ScanShort("�������Ա����:", &i);
		do {
			pUserTemp = pUserFront;
			pUserTemp = pUserTemp->next;
		} while (pUserTemp != NULL && pUserTemp->uid != i);
		if (pUserTemp == NULL)
			printf("û���ҵ�\n");
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
		if (ScanBoolean("ȷ���˳���(y/n)��"))
			op = -52;
	default:
		break;
}
if (op == -52)
break;
	}
}
