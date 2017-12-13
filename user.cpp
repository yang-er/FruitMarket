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

	// �ļ������ڵ�ʱ���ʼ��Ϊ������
	if (stat(pfUser, &pStat) == -1)
	{
		pUserTemp = (struct user*) malloc(sizeof(struct user));
		memset(pUserTemp, 0x00, sizeof(struct user));
		strcpy(pUserTemp->name, "�ֽ�");
		pUserTemp->uid = -1;
		pUserFront = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
		return;
	}

	// ����ļ�������
	if (pStat.st_size % sizeof(struct user) != 0)
		DataNotFulfilled(NULL, pfUser);

	// ���ļ�
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
