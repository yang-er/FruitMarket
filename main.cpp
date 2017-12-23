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
		flush_data();
	}
	else
	{
		// ����pTime��pCurrentDate
		pCurrentDate = localtime(&pTicketRear->time);
		pCurrentDate->tm_min = 0;
		pCurrentDate->tm_hour = 0;
		pCurrentDate->tm_sec = 0;
		pTime = mktime(pCurrentDate);

		// ���ʱ��
		printf("�������ڣ�%d��%d��%d�ա�\n",
			1900 + pCurrentDate->tm_year,
			pCurrentDate->tm_mon + 1,
			pCurrentDate->tm_mday);
	}
	sleep(500);
	clear();
	menu_main();
	SaveUserToFile();
	SaveTicketToFile();
	SaveStockToFile();
	printf("����������ϣ������˳�. . . ");
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
		printf("��ǰʱ�䣺%4d��%d��%d�ա�\n", pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday);
		op = ScanOption("��ѡ����룺", '1', '5');
		switch (op)
		{
			case '1': menu_stock(); break;
			case '2': menu_user(); break;
			case '3': menu_ticket(); break;
			case '4': push_date(); flush_data(); break;
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
		pCurrentDate->tm_mday += 1;
		pTime = mktime(pCurrentDate);
	}
	
	printf("�ѽ���%d��%d��%d�ա�\n", pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday);
	sleep(1000);
}

void flush_data()
{
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
}
