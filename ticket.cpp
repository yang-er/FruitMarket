#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "ticket.h"

ticket *pTicketFront = NULL;
ticket *pTicketRear = NULL;
ticket *pTicketTemp = NULL;
const char *pfTicket = "ticket.dat";

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
	return false;
}

void OutputTicket(ticket* ticket) 
{
}

void OutputAllTickets() 
{
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

void _ticket_test()
{
	/*
	char op;
	while (1)
	{
		printf("1.���� 2.���� 3.��ⷿ 4.���� 5.�˳�\n");
		ScanOption("��ѡ����룺", '1', '5', &op);
		switch (op)
		{
		case '1':
			SaveStockToFile();
			break;
		case '2':
			LoadStockFromFile();
			break;
		case '3':
			OutputStock();
			break;
		case '4':
			AddStock();
			break;
		case '5':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
		default:
			break;
		}
		if (op == -52)
			break;
	}
	*/
}