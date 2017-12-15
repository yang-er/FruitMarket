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

	// ����ڴ��е��û�
	while (pUserFront != NULL)
	{
		pUserTemp = pUserFront;
		pUserFront = pUserFront->next;
		pUserTemp->next = NULL;
		_free(pUserTemp, user);
	}
	pUserRear = NULL;
	pUserTemp = NULL;

	// �ļ������ڵ�ʱ���ʼ��Ϊ������
	if (stat(pfUser, &pStat) == -1)
	{
		_alloc(pUserTemp, user);
		strcpy(pUserTemp->name, "�ֽ�");
		pUserTemp->uid = -1;
		pUserFront = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
		return;
	}

	// ����ļ�������
	if (pStat.st_size % sizeof(user) != 0)
		DataNotFulfilled(NULL, pfUser);

	// ���ļ�
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
		if (pUserTemp->balance + credit > 1000000 || pUserTemp->balance + credit < 0)
		{
			printf("�������ƣ���ֵʧ�ܡ�\n");
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
			printf("���㣬�޷��û�Ա�����ѡ�\n");
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

		// ���벢��⿨��
		ScanShort("�����뿨�ţ�", &pUserTemp->uid);
		if (GetCardById(pUserTemp->uid) != NULL)
		{
			printf("��Ա��%04d�Ѵ��ڣ�\n", pUserTemp->uid);
			_free(pUserTemp, user);
			pUserTemp = NULL;
			continue;
		}
		ScanText("������ֿ���������", pUserTemp->name, 21);

		// ���벢���������
		double money;
		ScanDouble("�������Ա������", &money);
		pUserTemp->balance = cent(money);
		if (pUserTemp->balance > 1000000 || pUserTemp->balance < 0)
		{
			printf("�������ƣ�����ʧ�ܡ�\n");
			_free(pUserTemp, user);
			pUserTemp = NULL;
			continue;
		}

		// �����
		pUserRear->next = pUserTemp;
		pUserRear = pUserRear->next;
		pUserTemp = NULL;

		// ����Ƿ����
	} while (ScanBoolean("�Ƿ�������룿(y/n)��"));
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
	ScanShort("�������Ա���ţ�", &i);
	pUserTemp = pUserFront;
	while (pUserTemp->next != NULL && pUserTemp->next->uid != i)
		pUserTemp = pUserTemp->next;
	if (pUserTemp->next == NULL)
	{
		printf("�û�%04hd�����ڣ�\n", i);
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
	printf("|  ������%s\n", current->name);
	printf("|  ���ţ�%04hd\n", current->uid);
	printf("|  ����%.2lf\n", dollar(current->balance));
	printf("|  ���ã���%.2lf\n", dollar(current->todayUsage));
	printf("|\n");
	printf("==================\n");
	return false;
}

void ListAllVips()
{
	printf("==================\n");
	printf("|    ��Ա��Ϣ\n");
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
		printf("�û�%04hd�����ڣ�\n", uid);
		return false;
	}
	if (ScanBoolean("�Ƿ��޸Ļ�Ա������(y/n)��"))
	{
		ScanText("�����ƣ�", pUserTemp->name, 20);
	}
	pUserTemp = NULL;
	return true;
}

void PrintVip()
{
	short uid;
	ScanShort("�������Ա���ţ�", &uid);
	pUserTemp = GetCardById(uid);
	if (pUserTemp == NULL)
	{
		printf("û���ҵ��û�Ա��\n");
	}
	else
	{
		printf("==================\n");
		ListVip(pUserTemp);
		pUserTemp = NULL;
	}
}

void ChargeInConsole()
{
	short uid;
	double money;
	int credit;

	// �����Ա����
	ScanShort("�������Ա���ţ�", &uid);
	pUserTemp = GetCardById(uid);
	if (pUserTemp == NULL)
	{
		printf("�û�%04hd�����ڣ�\n", uid);
		sleep(500);
		return;
	}

	// �����ֵ���
	ScanDouble("�������ֵ��", &money);
	if (money <= 0 || money > 1000)
	{
		printf("��ֵʧ�ܣ�����������Ľ�\n");
		sleep(500);
	}
	else
	{
		credit = cent(money);
		if (ChargeToCard(uid, credit, true))
			printf("��ֵ�ɹ���\n");
	}
}

void _user()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    �û�ϵͳ\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.�����Ա\n");
		printf("|   2.��Ա��ֵ\n");
		printf("|   3.�޸���Ϣ\n");
		printf("|   4.ɾ����Ա\n");
		printf("|   5.��ѯ��Ա\n");
		printf("|   6.�г���Ա\n");
		printf("|   7.�˳�\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("��ѡ����룺", '1', '7');
		printf("\n");
		switch (op)
		{
		case '1':
			CreateCard();
			sleep(500);
			break;
		case '5':
			PrintVip();
			pause();
			break;
		case '6':
			ListAllVips();
			pause();
			break;
		case '4':
			if(CrashCard())
				printf("ɾ�����ɹ���\n");
			sleep(500);
			break;
		case '7':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
			break;
		case '2':
			ChargeInConsole();
			sleep(500);
			break;
		case '3':
			short i1;
			ScanShort("�������Ա���ţ�", &i1);
			ChangeVip(i1);
			printf("�޸Ľ�����\n");
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
