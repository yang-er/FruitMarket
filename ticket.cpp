#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "ticket.h"
#include "user.h"
#include "stock.h"

ticket *pTicketFront = NULL;
ticket *pTicketRear = NULL;
ticket *pTicketTemp = NULL;
const char *pfTicket = "ticket.dat";

ticket *FindTicket(short tid)
{
	ticket* temp;
	temp = pTicketFront;
	while (temp != NULL && temp->tid != tid)
		temp = temp->next;
	return temp;
}

void LoadTicketFromFile()
{
	struct stat pStat;

	// ����ڴ��е���Ϣ
	while (pTicketFront != NULL)
	{
		pTicketTemp = pTicketFront;
		pTicketFront = pTicketFront->next;
		pTicketTemp->next = NULL;
		_free(pTicketTemp, ticket);
	}
	pTicketRear = NULL;
	pTicketTemp = NULL;

	// �ļ������ڵ�ʱ���ʼ��Ϊ������
	if (stat(pfTicket, &pStat) == -1)
	{
		_alloc(pTicketTemp, ticket);
		pTicketFront = pTicketTemp;
		pTicketRear = pTicketTemp;
		pTicketTemp = NULL;
		return;
	}

	// ����ļ�������
	if (pStat.st_size % sizeof(ticket) != 0)
		DataNotFulfilled(NULL, pfTicket);

	// ���ļ�
	FILE *pFile = fopen(pfTicket, "r");
	CheckFile(pFile, pfTicket);
	for (int i = 0; i < pStat.st_size / sizeof(ticket); i++)
	{
		_alloc(pTicketTemp, ticket);
		fread(pTicketTemp, sizeof(ticket), 1, pFile);
		if (pTicketFront == NULL) pTicketFront = pTicketTemp;
		if (pTicketRear != NULL) pTicketRear->next = pTicketTemp;
		pTicketRear = pTicketTemp;
		pTicketTemp = NULL;
	}
	fclose(pFile);
	return;
}

bool SaveTicketToFile()
{
	FILE *pFile = fopen(pfTicket, "w+");
	CheckFile(pFile, pfTicket);
	while (pTicketFront != NULL)
	{
		pTicketTemp = pTicketFront;
		pTicketFront = pTicketFront->next;
		pTicketTemp->next = NULL;
		fwrite(pTicketTemp, sizeof(ticket), 1, pFile);
		_free(pTicketTemp, ticket);
	}
	pTicketRear = NULL;
	pTicketTemp = NULL;
	fclose(pFile);
	return true;
}

// �ͷŲ�����
#define doClean(p) do { \
			_free(pTicketTemp, ticket); \
			pTicketTemp = NULL; \
			return p; \
		} while (false)
#pragma warning (disable: 4003)

static bool payOne(int sum)
{
	// ��Ա�� or �ֽ�
	bool bContinue;
	do {
		ScanShort("�������Ա���ţ��ֽ�Ϊ-1����", &pTicketTemp->vipCard, true);
		pUserTemp = GetCardById(pTicketTemp->vipCard);
	} while (pUserTemp == NULL && printf("û���ҵ��û�Ա��\n"));

	// ���ֽ�
	if (pTicketTemp->vipCard == -1)
	{
		double c;
		do {
			ScanDouble("�����������ֽ�������", &c);
			pTicketTemp->given = cent(c);
			bContinue = pTicketTemp->given < sum;
			if (bContinue) printf("���ܵ���Ǯ��\n");
			if (bContinue && !ScanBoolean("�Ƿ���������ֽ�������(y/n)��")) doClean(false);
		} while (bContinue);
	}
	// �ջ�Ա��
	else
	{
		while (pUserTemp->balance < sum)
		{
			if (ScanBoolean("���㣬�Ƿ����̳�ֵ��(y/n)��"))
			{
				ChargeInConsole(pTicketTemp->vipCard);
			}
			else
			{
				if (ScanBoolean("�Ƿ������������ʹ���ֽ���(y/n)��"))
				{
					return true;
				}
				else
				{
					printf("������ֵ������ʧ�ܣ��˳���. . . \n");
					doClean(false);
				}
				break;
			}
		}
		pTicketTemp->given = pUserTemp->balance;
	}

	return false;
}

static void addOne()
{
	_alloc(pTicketTemp, ticket);
	// ȷ��СƱ���
	pTicketTemp->tid = pTicketRear->tid + 1;

	// ȷ������ʱ��
	pTicketTemp->time = ScanTime("�������µ�ʱ�䣺");

	// ȷ�������������ܽ��
	printf("���²�����������0��\n");
	double c = 0;
	int d = 0, sum = 0;
	char msg[70];
	for (int i = 0; i < 5; i++)
	{
		if (warehouse[i].isSingled)
		{
			sprintf(msg, "������%s����������%.2lfԪ/%s��ʣ��%d��һ��%d������",
				warehouse[i].fruitName, dollar(warehouse[i].singlePrice), warehouse[i].tagName, warehouse[i].left, warehouse[i].boxCount);
			do { ScanInt(msg, &d); } while ((d < 0 || d > warehouse[i].left) && printf("�����������Ϸ���\n"));
			pTicketTemp->amount[i] = d;
			pTicketTemp->credit[i] = d * warehouse[i].singlePrice;
		}
		else
		{
			sprintf(msg, "������%s����������%.2lfԪ/%s��ʣ��%.2lf����",
				warehouse[i].fruitName, dollar(warehouse[i].singlePrice), warehouse[i].tagName, dollar(warehouse[i].left));
			do { ScanDouble(msg, &c); } while ((c < 0 || c > dollar(warehouse[i].left)) && printf("�����������Ϸ���\n"));
			pTicketTemp->amount[i] = cent(c);
			pTicketTemp->credit[i] = int(c * warehouse[i].singlePrice);
		}
		sum += pTicketTemp->credit[i];
	}

	// ֧��
	printf("����ȡ%.2lfԪ��\n", dollar(sum));
	while (payOne(sum));
	if (pTicketTemp == NULL) return;
	pTicketTemp->left = pTicketTemp->given - sum;
	ChargeToCard(pTicketTemp->vipCard, sum, false);
	pUserTemp = NULL;
	for (int i = 0; i < 5; i++)
	{
		warehouse[i].left -= pTicketTemp->amount[i];
		warehouse[i].sold += pTicketTemp->amount[i];
		warehouse[i].todayUsage += pTicketTemp->credit[i];
	}

	// �������������
	if (pTicketRear == NULL)
	{
		pTicketFront = pTicketTemp;
		pTicketRear = pTicketTemp;
	}
	else
	{
		pTicketRear->next = pTicketTemp;
		pTicketRear = pTicketTemp;
	}

	OutputTicket(pTicketTemp, true);
	pTicketTemp = NULL;
}

#undef doClean

bool AddTicket()
{
	do {
		addOne();
	} while (ScanBoolean("�Ƿ�����½�������(y/n)��"));
	
	return false;
}

void OutputTicket(ticket* ticket, bool isFull) 
{
	if (isFull)
	{
		printf("==============================================\n");
		printf("|                ˮ������Ʊ��                |\n");
	}
	printf("==============================================\n");
	printf("|                                            |\n");
	if (ticket->vipCard != -1)
	{
		pUserTemp = GetCardById(ticket->vipCard);
		if (pUserTemp == NULL)
			printf("|  �����ˣ���ɾ��      �����----          |\n");
		else
			printf("|  �����ˣ�%-10s  �����%04d          |\n", pUserTemp->name, pUserTemp->uid);
		pUserTemp = NULL;
	}
	printf("|  ���ʽ��%s    Ʊ�ݺţ�%04d          |\n", ticket->vipCard == -1 ? "�ֽ�  " : "��Ա��", ticket->tid);
	printf("|                                            |\n");
	int calc = int(ticket->time - pTime);
	printf("|  ����ʱ�䣺%04d��%2d��%2d�� %2d:%02d            |\n", 
		pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday, calc / 3600, calc / 60 % 60);
	printf("|--------------------------------------------|\n");
	printf("|  # ��Ʒ��           ����    ����     ���  |\n");
	int sum = 0;
	double count = 0, credit = 0;
	for (int i = 0; i < 5; i++)
	{
		if (pTicketTemp->amount[i] == 0) continue;
		sum += pTicketTemp->credit[i];
		credit = dollar(pTicketTemp->credit[i]);
		count = dollar(pTicketTemp->amount[i] * (warehouse[i].isSingled ? 100 : 1));
		printf("|  %d %-12s  %7.2lf %7.2lf %8.2lf  |\n",
			i+1, warehouse[i].fruitName, credit / count, count, credit);
	}
	printf("|--------------------------------------------|\n");
	printf("|  �ϼ�                            %8.2lf  |\n", dollar(sum));
	printf("|                                            |\n");
	if (ticket->vipCard == -1)
		printf("|  �տ%8.2lf      ���㣺%8.2lf        |\n", dollar(pTicketTemp->given), dollar(pTicketTemp->left));
	else
		printf("|  ԭ�У�%8.2lf      ��%8.2lf        |\n", dollar(pTicketTemp->given), dollar(pTicketTemp->left));
	printf("|                                            |\n");
	if (isFull)
	{
		printf("|  1���˻�����  3�����ʳ�ŵ   109��ȫԺ����  |\n");
		printf("|                                            |\n");
		printf("==============================================\n");
	}

}

void OutputAllTickets()
{
	// ��ʱ����
	double dbTemp;

	// ��ʼʱ��
	time_t ptStart = pTime;
	if (ScanBoolean("�Ƿ�ѡ��ʼʱ�䣿(y/n)��"))
		ptStart = ScanTime("���뿪ʼ��ʱ�䣺");

	// ����ʱ��
	time_t ptEnd = pTime + 86341;
	if (ScanBoolean("�Ƿ�ѡ�����ʱ�䣿(y/n)��"))
		ptEnd = ScanTime("���������ʱ�䣺");
	if (ptStart >= ptEnd) ptEnd = pTime + 86341;

	// �������
	int crMin = 0;
	if (ScanBoolean("�Ƿ����������ѣ�(y/n)��"))
	{
		ScanDouble("������������ѽ�", &dbTemp);
		if (dbTemp >= 0) crMin = cent(dbTemp);
	}

	// �������
	int crMax = -1;
	if (ScanBoolean("�Ƿ����������ѣ�(y/n)��"))
	{
		ScanDouble("������������ѽ�", &dbTemp);
		if (dbTemp > 0) crMax = cent(dbTemp);
		if (crMax < crMin) crMax = -1;
	}

	// �������������СƱ
	printf("==============================================\n");
	printf("|                ˮ������Ʊ��                |\n");
	pTicketTemp = pTicketFront->next;
	while (pTicketTemp != NULL)
	{
		int usage = pTicketTemp->given - pTicketTemp->left;
		if ((pTicketTemp->time >= ptStart) && (pTicketTemp->time <= ptEnd)
				&& (usage >= crMin) && (crMax == -1 || usage <= crMax))
			OutputTicket(pTicketTemp, false);
		pTicketTemp = pTicketTemp->next;
	}
	printf("==============================================\n");
}

bool ModifyTicket(short tid)
{
	if (ScanBoolean("�Ƿ�ͬʱ�䶯�����ȵĸĶ���(y/n)��"))
	{
		// TODO
	}
	else
	{
		pTicketTemp = FindTicket(tid);
		if (pTicketTemp == NULL)
		{
			printf("����%04hd�����ڣ�\n", tid);
			return false;
		}
		if (ScanBoolean("�Ƿ��޸Ĺ���ʱ�䣿(y/n)��"))
		{
			pTicketTemp->time = ScanTime("���������µ�ʱ�䣺");
		}
		pTicketTemp = NULL;
		return true;
	}
	return false; 
}

bool DeleteTicket(short tid)
{
	// �ҵ�СƱ��ǰһ���ڵ�
	pTicketTemp = pTicketFront;
	while (pTicketTemp->next != NULL && pTicketTemp->next->tid != tid)
		pTicketTemp = pTicketTemp->next;
	if (pTicketTemp->next == NULL)
	{
		printf("����%04hd�����ڣ�\n", tid);
		pTicketTemp = NULL;
		return false;
	}

	ticket *temp = pTicketTemp->next;
	pTicketTemp->next = temp->next;

	if (ScanBoolean("�Ƿ����̳��������ȵĸĶ���(y/n)��"))
	{
		int credit = 0;

		// �������Ӱ��
		for (int i = 0; i < 5; i++)
		{
			warehouse[i].left += temp->amount[i];
			warehouse[i].sold -= temp->amount[i];
			credit += temp->credit[i];
		}

		// �������Ӱ��
		if (pTicketTemp->vipCard == -1)
		{
			pUserTemp = GetCardById(temp->vipCard);
			if (pUserTemp == NULL || !ChargeToCard(temp->vipCard, 0, true))
			{
				printf("�޷����ص����ڣ������ֽ�%.2lfԪ��", dollar(credit));
				pUserTemp = NULL;
			}
		}

	}

	_free(temp, ticket);
	pTicketTemp = NULL;
	return true;
}

void ExportTickets()
{
	// �����ļ���
	char pFileName[30];
	sprintf(pFileName, "%04d-%d-%d �������Ѽ�¼.csv",
		pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday);

	// ���ļ�
	FILE *pFile;
	do {
		pFile = fopen(pFileName, "w+");
		if (pFile == NULL)
		{
			printf("�ļ�%s����ʧ�ܡ�\n", pFileName);
			if (ScanBoolean("�Ƿ����ԣ�(y/n)��")) continue;
		}
		break;
	} while (true);
	if (pFile == NULL) return;

	// ��ӡ��ͷ
	fprintf(pFile, "Ʊ��,ʱ��,������,����,�ϼ�,�տ�,����");
	for (int i = 0; i < 5; i++)
	{
		fprintf(pFile, ",%s����,%s���", warehouse[i].fruitName, warehouse[i].fruitName);
	}
	fprintf(pFile, "\n");

	// ��ӡÿ����¼
	pTicketTemp = pTicketFront->next;
	user *puser;
	int calc;
	while (pTicketTemp != NULL)
	{
		if (pTicketTemp->time < pTime || pTicketTemp->time > pTime + 86399)
		{
			pTicketTemp = pTicketTemp->next;
			continue;
		}
		calc = int(pTicketTemp->time - pTime);
		fprintf(pFile, "%04d,%d:%02d,", pTicketTemp->tid, calc / 3600, calc / 60 % 60);
		puser = GetCardById(pTicketTemp->vipCard);
		if (puser == NULL) fprintf(pFile, "��ɾ��,0000,");
		else fprintf(pFile, "%s,%04d,", puser->name, puser->uid);
		fprintf(pFile, "%.2lf,%.2lf,%.2lf",
			dollar(pTicketTemp->given - pTicketTemp->left),
			dollar(pTicketTemp->given), dollar(pTicketTemp->left));
		for (int i = 0; i < 5; i++)
			if (warehouse[i].isSingled)
				fprintf(pFile, ",%d,%.2lf", pTicketTemp->amount[i], dollar(pTicketTemp->credit[i]));
			else
				fprintf(pFile, ",%.2lf,%.2lf", dollar(pTicketTemp->amount[i]), dollar(pTicketTemp->credit[i]));
		fprintf(pFile, "\n");
		pTicketTemp = pTicketTemp->next;
	}

	// ������ӡ
	fclose(pFile);
	printf("��¼�ѵ�������%s����\n", pFileName);

}

void menu_ticket()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    СƱϵͳ\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.��Ӽ�¼\n");
		printf("|   2.����Ʊ��\n");
		printf("|   3.�г�����\n");
		printf("|   4.�޸ļ�¼\n");
		printf("|   5.ɾ����¼\n");
		printf("|   6.������Ϣ\n");
		printf("|   7.�˳�\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("��ѡ����룺", '1', '7');
		printf("\n");
		switch (op)
		{
		case '1': AddTicket(); break;
		case '2':
			short tid;
			ScanShort("�����빺�ﵥ�ţ�", &tid, false);
			pTicketTemp = FindTicket(tid);
			if (pTicketTemp == NULL)
			{
				printf("û���ҵ��ù����¼��\n");
			}
			else
			{
				OutputTicket(pTicketTemp, true);
				pTicketTemp = NULL;
			}
			pause();
			break;
		case '3': OutputAllTickets(); pause(); break;
		case '4': short i0; ScanShort("�����뵥��:", &i0, false); ModifyTicket(i0); break;
		case '5': short i; ScanShort("�����뵥�ţ�", &i, false); DeleteTicket(i); break;
		case '6': ExportTickets(); break;
		case '7': if (ScanBoolean("ȷ���˳���(y/n)��")) op = -52; break;
		default: break;
		}
		
		if (op == -52)
		{
			SaveTicketToFile();
			SaveUserToFile();
			SaveStockToFile();
			LoadStockFromFile();
			LoadUserFromFile();
			LoadTicketFromFile();
			sleep(500);
			clear();
			break;
		}

		sleep(500);
		clear();
	}
}