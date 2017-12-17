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
		ScanShort("请输入序号：", &pTicketTemp->tid);
		if (GetCardBytid(pTicketTemp->tid) != NULL)
		{
			printf("小票%04d已存在！\n", pTicketTemp->tid);
			pTicketTemp->tid = NULL;
			continue;
		}
		ScanInt("请输入水果种类:", &pTicketTemp->fruit);
		ScanInt("请输入水果购买数量：", &pTicketTemp->amount[pTicketTemp->fruit]);
		ScanInt("请输入水果购买金额：", &pTicketTemp->credit[pTicketTemp->fruit]);
		ScanShort("请输入会员卡号(现金为-1)：", &pTicketTemp->vipCard);
		if (GetCardById(pTicketTemp->vipCard) == NULL)
		{
			printf("没有找到该会员。\n");
			continue;
		}
		if (pTicketTemp->vipCard == -1)
		{
			ScanInt("请输入收入现金数量：", &pTicketTemp->given);
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
	} while (ScanBoolean("是否继续输入？(y/n)："));
	return false;
}

void OutputTicket(ticket* ticket) 
{
	printf("|\n");
	printf("|  序号：%04hd\n", pTicketTemp->tid);
	printf("|  水果种类：");

	printf("|  购买数量：%d\n", pTicketTemp->amount[pTicketTemp->fruit]);
	printf("|  购买金额:￥%d\n", pTicketTemp->credit[pTicketTemp->fruit]);
	printf("|  收入现金:￥%d\n", pTicketTemp->given);
	printf("|  找零:￥%d\n", pTicketTemp->left);
	if(pTicketTemp->vipCard!=-1)
	ListVip(GetCardById(pTicketTemp->vipCard));
	printf("|\n");
	printf("==================\n");
}

void OutputAllTickets()
{
	printf("==================\n");
	printf("|    购物小票\n");
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
	ScanShort("请输入购物单号：", &tid);
	pTicketTemp = GetCardBytid(tid);
	if (pTicketTemp == NULL)
	{
		printf("没有找到该购物记录。\n");
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
		printf("|    小票系统\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.添加一张小票\n");
		printf("|   2.输出一张小票的信息\n");
		printf("|   3.按照号码查找小票\n");
		printf("|   4.修改小票内容\n");
		printf("|   5.删除小票\n");
		printf("|   6.查询大额购物信息\n");
		printf("|   7.查询某段时间内购物信息\n");
		printf("|   8.退出\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("请选择进入：", '1', '8');
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
			if (ScanBoolean("确定退出嘛(y/n)："))
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