#include "stdafx.h"
#include "scan.h"
#include "stock.h"
#include "user.h"
#include "ticket.h"

int main()
{
	printf("���ڼ�������. . . \n");
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	if (pTicketFront == pTicketRear)
	{
		SetCurrentDate();
	}
	else
	{
		// ����pTime��pCurrentDate
		LocalTime(&pDate, &pTicketRear->time);
		pDate.tm_min = 0;
		pDate.tm_hour = 0;
		pDate.tm_sec = 0;
		pTime = mktime(&pDate);

		// ���ʱ��
		printf("�������ڣ�%d��%d��%d�ա�\n",
			1900 + pDate.tm_year,
			pDate.tm_mon + 1,
			pDate.tm_mday);
	}
	flush_data();
	sleep(500);
	clear();
	menu_main();
	SaveTicketToFile();
	SaveUserToFile();
	SaveStockToFile();
	printf("����������ϣ������˳�. . . \n");
	sleep(500);
    return 0;
}

void menu_main()
{
	char op;
	while (true)
	{
		printf("====================\n");
		printf("|     ˮ���̵�     |\n");
		printf("====================\n");
		printf("|                  |\n");
		printf("|    1.������    |\n");
		printf("|    2.�û�����    |\n");
		printf("|    3.�����¼    |\n");
		printf("|    4.�ڶ���      |\n");
		printf("|    5.�˳�ϵͳ    |\n");
		printf("|                  |\n");
		printf("====================\n");
		printf("��ǰʱ�䣺%4d��%d��%d�ա�\n", pDate.tm_year + 1900, pDate.tm_mon + 1, pDate.tm_mday);
		op = ScanOption("��ѡ����룺", '1', '5');
		switch (op)
		{
			case '1': menu_stock(); break;
			case '2': menu_user(); break;
			case '3': menu_ticket(); break;
			case '4': push_date(); break;
			case '5': if (ScanBoolean("ȷ���˳���(y/n)��")) return; break;
			default: break;
		}
		clear();
	}
}

void push_date()
{
	if (!ScanBoolean("ֱ�ӽ�����һ�죿(y/n)��"))
	{
		SetCurrentDate();
	}
	else
	{
		ExportTickets();
		pDate.tm_mday += 1;
		pTime = mktime(&pDate);
	}
	
	printf("�ѽ���%d��%d��%d�ա�\n", pDate.tm_year + 1900, pDate.tm_mon + 1, pDate.tm_mday);
	bFresh = false;
	flush_data();
	sleep(1000);
}

void flush_data()
{
	if (bFresh) return;
	for (pUserTemp = pUserFront; pUserTemp != NULL; pUserTemp = pUserTemp->next)
		pUserTemp->todayUsage = 0;
	for (int i = 0; i < 5; i++)
		warehouse[i].todayUsage = 0;

	int sum;
	for (pTicketTemp = pTicketFront->next; pTicketTemp != NULL; pTicketTemp = pTicketTemp->next)
	{
		if (pTicketTemp->time >= pTime && pTicketTemp->time <= pTime + 86399)
		{
			sum = 0;
			for (int i = 0; i < 5; i++)
			{
				sum += pTicketTemp->credit[i];
				warehouse[i].todayUsage += pTicketTemp->credit[i];
			}
			pUserTemp = GetCardById(pTicketTemp->vipCard);
			if (pUserTemp != NULL)
				pUserTemp->todayUsage += sum;
			pUserTemp = NULL;
		}
	}

	bFresh = true;
}
