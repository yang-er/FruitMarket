#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "math.h"
FILE *file;
/// <summary>
/// ���ļ������û���Ϣ��
/// </summary>
struct user *LoadUserFromFile()
{
	
	return NULL;
}

/// <summary>
/// ���û���Ϣ���浽�ļ���
/// </summary>
bool SaveUserToFile(struct user* vip)
{
	if ((file = fopen("user.dat", "w+")) == NULL)
	{
		printf("��ʧ��\n");
		exit(0);
	}
	
	return false;
}

bool ChargeToCard(int uid, int credit, bool isAdd)
{
	return false;
}

struct user *createCard()
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
	return head;
}

bool CrashCard(int uid)
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

bool ListAllVips(struct user* vipHead)
{
	while (vipHead != NULL)
	{
		ListVip(vipHead);
		vipHead = vipHead->next;
	}
	return false;
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
	CrashCard(i);
}
void _user_test()
{
	struct user *p=NULL;
	char op;
	while (1)
	{
	printf("1.����������Ա������ 2.���ػ�Ա��Ϣ 3.���ص�����Ա 4.����ȫ����Ա 5.ɾ��������Ա 6.�˳�\n");
	ScanOption("��ѡ����룺", '1', '6', &op);
	switch (op)
	{
	case '1':
		p=createCard();
		break;
	case '2':
		LoadUserFromFile();
		break;
	case '3':
		printvip(p);
		break;
	case '4':
		ListAllVips(p);
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
