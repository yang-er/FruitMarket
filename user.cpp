#include "stdafx.h"
#include "scan.h"
#include "math.h"
#include "user.h"
#include "structs.h"

struct user *pUserFront = NULL;
struct user *pUserRear = NULL;
struct user *pUserTemp = NULL;
const char *pfUser = "user.dat";

void LoadUserFromFile()
{
	struct stat pStat;
	stat(pfUser, &pStat);

	// ����ڴ��е��û�
	while (pUserFront != NULL)
	{
		pUserTemp = pUserFront;
		pUserFront = pUserFront->next;
		pUserTemp->next = NULL;
		memset(pUserTemp, 0x00, sizeof(struct user));
		free(pUserTemp);
	}
	pUserRear = NULL;
	pUserTemp = NULL;

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
		fwrite(pUserTemp, sizeof(struct user), 1, pFile);
		memset(pUserTemp, 0x00, sizeof(struct user));
		free(pUserTemp);
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
		pUserTemp = (struct user *)malloc(sizeof(struct user));
		memset(pUserTemp, 0x00, sizeof(struct user));
		ScanShort("�����뿨�ţ�", &pUserTemp->uid);
		if (GetCardById(pUserTemp->uid) != NULL)
		{
			printf("��Ա��%04d�Ѵ��ڣ�\n", pUserTemp->uid);
			free(pUserTemp);
			pUserTemp = NULL;
			continue;
		}
		ScanText("������ֿ���������", pUserTemp->name, 21);
		double money;
		ScanDouble("�������Ա����", &money);
		pUserTemp->balance = (int)floor(money * 100 + 0.5);
		pUserRear->next = pUserTemp;
		pUserRear = pUserRear->next;
		pUserTemp = NULL;
	} while (ScanBoolean("�Ƿ�������룿(y/n)��"));
}

struct user *GetCardById(short uid)
{
	struct user* temp;
	temp = pUserFront;
	while (temp != NULL && temp->uid != uid)
		temp = temp->next;
	return temp;
}

bool CrashCard()
{
	short i;
	ScanShort("�������Ա����:", &i);
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
		struct user *temp = pUserTemp->next;
		pUserTemp->next = temp->next;
		memset(temp, 0x00, sizeof(struct user));
		free(temp);
		pUserTemp = NULL;
		return true;
	}
}

bool ListVip(struct user* current)
{
	printf("|\n");
	printf("|  ������%s\n", current->name);
	printf("|  ���ţ�%04hd\n", current->uid);
	printf("|  ��%d.%02d\n", current->balance / 100, current->balance % 100);
	printf("|  ���ã�%d.%02d\n", current->todayUsage / 100, current->todayUsage % 100);
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
		memset(pUserTemp->name, 0x00, 21);
		ScanText("�����ƣ�", pUserTemp->name, 20);
	}
	return true;
}

void _user()
{
	_clear();
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
		ScanOption("��ѡ����룺", '1', '7', &op);
		printf("\n");
		switch (op)
		{
		case '1':
			CreateCard();
			_sleep(500);
			_clear();
			break;
		case '5':
			// ��ӡ������Ա
			{
				short i;
				ScanShort("�������Ա���ţ�", &i);
				pUserTemp = GetCardById(i);
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
				printf("\n�����������... ");
				rewind(stdin);
				getchar();
				rewind(stdin);
				_clear();
			}
			break;
		case '6':
			// ��ӡ���л�Ա
			ListAllVips();
			printf("\n�����������... ");
			rewind(stdin);
			getchar();
			rewind(stdin);
			_clear();
			break;
		case '4':
			if(CrashCard())
				printf("ɾ�����ɹ���\n");
			_sleep(500);
			_clear();
			break;
		case '7':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
			break;
		case '2':
			// ��������ֵ
			{
				short j;
				double m;
				int n;
				ScanShort("�������Ա���ţ�", &j);
				ScanDouble("�������ֵ��", &m);
				if (m <= 0 || m > 1000)
				{
					printf("��ֵʧ�ܣ�����������Ľ�\n");
					_sleep(500);
				}
				else
				{
					n = (int)floor(m * 100 + 0.5);
					if (ChargeToCard(j, (int)floor(m * 100 + 0.5), true))
						printf("��ֵ�ɹ���\n");
				}
				_sleep(500);
				_clear();
			}
			break;
		case '3':
			short i1;
			ScanShort("�������Ա����:", &i1);
			ChangeVip(i1);
			printf("�޸Ľ�����\n");
			_sleep(500);
			_clear();
			break;
		default:
			break;
		}
		if (op == -52)
		{
			SaveUserToFile();
			LoadUserFromFile();
			_sleep(500);
			_clear();
			break;
		}
	}
}
