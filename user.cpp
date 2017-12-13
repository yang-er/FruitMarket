#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"
#include "structs.h"

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
	pUserTemp = pUserFront;
	do {
		pUserTemp = pUserTemp->next;
	} while (pUserTemp != NULL && pUserTemp->uid != uid);
	if (pUserTemp == NULL)
	{
		printf("û���ҵ�\n");
		return false;
	}
	if (isAdd) {
		if (pUserTemp->balance + credit > 1000000)
			printf("��ֵʧ��");
		else
			pUserTemp->balance = pUserTemp->balance + credit;
	}
	else
	{
		if (pUserTemp->balance - credit < 0)
			printf("����,�޷��û�Ա������");
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
		ScanText("������ֿ���ǩ��:", pUserTemp->name, 21);
		ScanShort("��������:", &pUserTemp->uid);
			q = pUserFront;
				do {
					q = q->next;
				} while (q != NULL && q->uid != pUserTemp->uid);
				if (q != NULL)
				{
					printf("��Ա�Ѵ���,����������\n");
					ScanShort("��������:", &pUserTemp->uid);
				}
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
	printf("1.����������Ա 2.���ػ�Ա��Ϣ 3.���ص�����Ա 4.����ȫ����Ա 5.ɾ��������Ա 6.�˳� 7.��ֵ������\n");
	ScanOption("��ѡ����룺", '1', '7', &op);
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
	case '4':
		ListAllVips();
		break;
	case '5':
		CrashCard();
		break;
	case '6':
		if (ScanBoolean("ȷ���˳���(y/n)��"))
			op = -52;
	case '7':
		short j;
		int k;
		double m;
		int n;
		ScanShort("�������Ա����(�ֽ�Ϊ'-1'):", &j);
		if (j == -1)
			break;
		bool isadd;
		ScanInt("�������ֵ������,1.��ֵ,0.����", &k);
		if (k == 1)
			isadd = true;
		if (k == 0)
			isadd = false;
		ScanDouble("�������ֵ���:", &m);
		if (m <= 0 || m > 1000)
			printf("��ֵʧ��");
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
