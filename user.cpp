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

	FILE* pFile = NULL;
	int count = OpenFile(&pFile, pfUser, sizeof(user));

	// �����ݵ�ʱ���ʼ��Ϊ������
	if (count == 0)
	{
		_alloc(pUserTemp, user);
		strcpy(pUserTemp->name, "�ֽ�");
		pUserTemp->uid = -1;
		pUserFront = pUserTemp;
		pUserRear = pUserTemp;
		pUserTemp = NULL;
		return;
	}

	// ���������ȡ
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
	} while (pFile == NULL && ScanBoolean("�ļ�user.dat�޷��򿪣��Ƿ����ԣ�(y/n)��"));

	if (pFile == NULL)
	{
		printf("�����ļ����棬�������Ľ���������. . . \n");
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
		ScanShort("�����뿨�ţ�", &pUserTemp->uid, false);
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
		ScanDouble("�������Ա����", &money);
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
	ScanShort("�������Ա���ţ�", &i, false);
	if (!ScanBoolean("ȷ��Ҫɾ�������Ա��(y/n)��"))
		return false;
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
		if (pUserTemp->next == NULL) pUserRear = pUserTemp;
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
	printf("|  ��%.2lf\n", dollar(current->balance));
	printf("|  ���ã�%.2lf\n", dollar(current->todayUsage));
	printf("|\n");
	printf("==================\n");
	return false;
}

void ListAllVips()
{
	flush_data();
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
		ScanText("�����ƣ�", pUserTemp->name, 21);
	}
	pUserTemp = NULL;
	return true;
}

void PrintVip()
{
	flush_data();
	short uid;
	ScanShort("�������Ա���ţ�", &uid, true);
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

void ChargeInConsole(short uid)
{
	double money;
	int credit;

	if (uid == -2)
	{
		// �����Ա����
		ScanShort("�������Ա���ţ�", &uid, false);
		pUserTemp = GetCardById(uid);
		if (pUserTemp == NULL)
		{
			printf("�û�%04hd�����ڣ�\n", uid);
			sleep(500);
			return;
		}
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

void menu_user()
{
	clear();
	char op;
	short i1;
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
			case '1': CreateCard(); break;
			case '2': ChargeInConsole(-2); break;
			case '3': ScanShort("�������Ա���ţ�", &i1, false); ChangeVip(i1); printf("�޸Ľ�����\n"); break;
			case '4': if(CrashCard()) printf("ɾ�����ɹ���\n"); break;
			case '5': PrintVip(); _pause(); break;
			case '6': ListAllVips(); _pause(); break;
			case '7': if (ScanBoolean("ȷ���˳���(y/n)��")) op = -52; break;
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
