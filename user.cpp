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
	pUserTemp = pUserFront;
	while (pUserTemp != NULL && pUserTemp->uid != uid)
	{
		pUserTemp = pUserTemp->next;
	}

	if (pUserTemp == NULL)
	{
		printf("û���ҵ�\n");
		return false;
	}
	if (isAdd) {
		if (pUserTemp->balance + credit > 1000000)
			printf("��ֵʧ��\n");
		else
			pUserTemp->balance = pUserTemp->balance + credit;
	}
	else
	{
		if (pUserTemp->balance - credit < 0 && uid != -1)
			printf("����,�޷��û�Ա������\n");
		else {
			pUserTemp->balance = pUserTemp->balance - credit;
			pUserTemp->todayUsage += credit;
		}
	}
	
	return false;
}

void CreateCard()
{
	struct user *q=NULL;
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
	ScanShort("�������Ա����:", &i);
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
	printf("|    ��Ա��Ϣ\n");
	printf("==================\n");
	printf("\n");
	printf("��Ա����:%s\n", current->name);
	printf("��Ա����:%04hd\n", current->uid);
	printf("�û����:%d.%02d\n", current->balance / 100, current->balance % 100);
	printf("���տ���:%d.%02d\n", current->todayUsage / 100, current->todayUsage % 100);
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
	printf("1.����������Ա 2.�����Ա��Ϣ 3.���ػ�Ա��Ϣ 4.��ӡ������Ա 5.��ӡȫ����Ա 6.ɾ��������Ա  7.��ֵ������ 8.�˳�\n");
	ScanOption("��ѡ����룺", '1', '8', &op);
	switch (op)
	{
	case '1':
		CreateCard();
		break;
	case '2':
		SaveUserToFile();
		break;
	case '3':
		LoadUserFromFile();
		break;
	case '4':
		short i;
		ScanShort("�������Ա����:", &i);
		pUserTemp = pUserFront;
		do {
			pUserTemp = pUserTemp->next;
		} while (pUserTemp != NULL && pUserTemp->uid != i);
		if (pUserTemp == NULL)
			printf("û���ҵ�\n");
		else
			ListVip(pUserTemp);
		pUserTemp = NULL;
		break;
	case '5':
		ListAllVips();
		break;
	case '6':
		CrashCard();
		break;
	case '8':
		if (ScanBoolean("ȷ���˳���(y/n)��"))
			op = -52;
		break;
	case '7':
		//short j;
		int j;
		int k;
		double m;
		int n;
		//ScanShort("�������Ա����(�ֽ�Ϊ'-1'):", &j);
		ScanInt("�������Ա����(�ֽ�Ϊ'-1'):", &j);
		bool isadd;
		ScanInt("�������ֵ������,1.��ֵ,0.����:", &k);
		if (k == 1) {
			isadd = true;
			ScanDouble("�������ֵ���:", &m);
		}
		if (k == 0) {
			isadd = false;
			ScanDouble("���������ѽ��:", &m);
		}
		
		if (m <= 0 || m > 1000)
			printf("��ֵʧ��\n");
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
