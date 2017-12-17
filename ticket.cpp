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

ticket *GetCardBytid(short tid)
{
	ticket* temp;
	temp = pTicketFront;
	while (temp != NULL && temp->tid != tid)
		temp = temp->next;
	return temp;
}

void LoadTicketFromFile()
{
	return;
}

bool SaveTicketToFile()
{
	return false;
}

bool AddTicket()
{ 
	_alloc(pTicketTemp, ticket);
	do {
		_alloc(pTicketTemp, ticket);
		ScanShort("��������ţ�", &pTicketTemp->tid);
		if (GetCardBytid(pTicketTemp->tid) != NULL)
		{
			printf("СƱ%04d�Ѵ��ڣ�\n", pTicketTemp->tid);
			pTicketTemp->tid = NULL;
			continue;
		}
		ScanInt("������ˮ������:", &pTicketTemp->fruit);
		ScanInt("������ˮ������������", &pTicketTemp->amount[pTicketTemp->fruit]);
		ScanInt("������ˮ�������", &pTicketTemp->credit[pTicketTemp->fruit]);
		ScanShort("�������Ա����(�ֽ�Ϊ-1)��", &pTicketTemp->vipCard);
		if (GetCardById(pTicketTemp->vipCard) == NULL)
		{
			printf("û���ҵ��û�Ա��\n");
			continue;
		}
		if (pTicketTemp->vipCard == -1)
		{
			ScanInt("�����������ֽ�������", &pTicketTemp->given);
			pTicketTemp->left = pTicketTemp->credit[pTicketTemp->fruit] - pTicketTemp->given;
		}
		else
		{
			pTicketTemp->given = 0;
			pTicketTemp->left = 0;
			ChargeToCard(pTicketTemp->vipCard, pTicketTemp->credit[pTicketTemp->fruit], 0);
		}
		if (pTicketRear == NULL)
			pTicketFront = pTicketTemp;
		else
		{
			pTicketRear->next = pTicketTemp;
			pTicketRear = pTicketRear->next;
		}
		pTicketTemp = NULL;
	} while (ScanBoolean("�Ƿ�������룿(y/n)��"));
	return false;
}

void OutputTicket(ticket* ticket) 
{
	printf("|\n");
	printf("|  ��ţ�%04hd\n", pTicketTemp->tid);
	printf("|  ˮ�����ࣺ");

	printf("|  ����������%d\n", pTicketTemp->amount[pTicketTemp->fruit]);
	printf("|  ������:��%d\n", pTicketTemp->credit[pTicketTemp->fruit]);
	printf("|  �����ֽ�:��%d\n", pTicketTemp->given);
	printf("|  ����:��%d\n", pTicketTemp->left);
	if(pTicketTemp->vipCard!=-1)
	ListVip(GetCardById(pTicketTemp->vipCard));
	printf("|\n");
	printf("==================\n");
}

void OutputAllTickets()
{
	printf("==================\n");
	printf("|    ����СƱ\n");
	printf("==================\n");
	pTicketTemp = pTicketFront->next;
	while (pTicketTemp != NULL)
	{
		OutputTicket(pTicketTemp);
		pTicketTemp = pTicketTemp->next;
	}
}

ticket *FindTicket(short tid)
{
	return NULL;
}

bool ModifyTicket(short tid)
{
	return false; 
}

bool DeleteTicket(short tid)
{ 
	return false; 
}

void printticket()
{
	short tid;
	ScanShort("�����빺�ﵥ�ţ�", &tid);
	pTicketTemp = GetCardBytid(tid);
	if (pTicketTemp == NULL)
	{
		printf("û���ҵ��ù����¼��\n");
	}
	else
	{
		printf("==================\n");
		OutputTicket(pTicketTemp);
		pTicketTemp = NULL;
	}
}
void _ticket_test()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    СƱϵͳ\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.���һ��СƱ\n");
		printf("|   2.���һ��СƱ����Ϣ\n");
		printf("|   3.���պ������СƱ\n");
		printf("|   4.�޸�СƱ����\n");
		printf("|   5.ɾ��СƱ\n");
		printf("|   6.��ѯ������Ϣ\n");
		printf("|   7.��ѯĳ��ʱ���ڹ�����Ϣ\n");
		printf("|   8.�˳�\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("��ѡ����룺", '1', '8');
		printf("\n");
		switch (op)
		{
		case '1':
			AddTicket();
			sleep(500);
			break;
		case '2':
			printticket();
			pause();
			break;
		case '3':
			pause();
			break;
		case '4':
			sleep(500);
			break;
		case '5':
			sleep(500);
			break;
		case '6':
			sleep(500);
			break;
		case '7':
			sleep(500);
			break;
		case '8':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
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