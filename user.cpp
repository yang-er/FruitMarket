#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"

struct user *pUserFront = NULL;
struct user *pUserRear = NULL;
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
	struct user *head = NULL;
	struct user *p1, *p2 = NULL;
	int i = 1, j = 1;
	while (j != 0)
	{
		p1 = (struct user *)malloc(sizeof(struct user));
		ScanText("������ֿ���ǩ��:", p1->name, 21);
		ScanShort("��������:", &p1->uid);
		ScanInt("�������Ա�����:", &p1->balance);
		ScanInt("�����뵱�տ���:", &p1->todayUsage);
		if (i == 1)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		i++;
			ScanInt("�������Ƿ��������:1.��,0.��", &j);
	}
	p2->next = NULL;
}

bool CrashCard()
{
	return false;
}

bool ListVip(struct user* current)
{
	printf("==================\n");
	printf("|    ��Ա��Ϣ\n");
	printf("==================\n");
	printf("\n");
	printf("��Ա����:%s\n", current->name);
	printf("��Ա����:%d\n", current->uid);
	printf("�û����:%d\n", current->balance);
	printf("���տ���:%d\n", current->todayUsage);
	return false;
}

void ListAllVips()
{
	pUserTemp = pUserFront;
	while (pUserTemp != NULL)
	{
		ListVip(pUserTemp);
		pUserTemp = pUserTemp->next;
	}
}

void printvip(struct user* vipHead) {
	struct user *p1=NULL;
	short i;
	bool flag = false;
	ScanShort("�������Ա����", &i);
	 do{
		 p1 = vipHead;
		vipHead = vipHead->next;
	 } while (vipHead != NULL && p1->uid != i);
	if (p1->uid == i)
		flag = true;
	if (!flag)
		printf("û���ҵ�\n");
	else
		ListVip(p1);
}
void inputuid()
{
	short i;
	ScanShort("�������Ա����:", &i);
	CrashCard();
}
void _user_test()
{
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
		printvip(NULL);
		break;
	case '4':
		ListAllVips();
		break;
	case '5':
		inputuid();
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
