#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

extern void menu_main();

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
		printf("1.�ǣ�������  2.�ǣ���ά��  3.�ǣ���Ӣ��  4.�ǣ������� 5.�ǣ�����\n");
		op = ScanOption("��ѡ����룺", '1', '5');
		switch (op)
		{
		case '1':
			menu_stock();
			break;
		case '2':
			menu_user();
			break;
		case '3':
			menu_ticket();
			break;
		case '5':
			PushDate();
			break;
		case '4':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
			break;
		default:
			break;
		}
		if (op == -52)
			break;
	}
}

void PushDate()
{
	ExportTickets();
	pCurrentDate->tm_mday += 1;
	pTime = mktime(pCurrentDate);
	for (int i = 0; i < 5; i++)
		warehouse[i].todayUsage = 0;
	for (pUserTemp = pUserFront; pUserTemp != NULL; pUserTemp = pUserTemp->next)
		pUserTemp->todayUsage = 0;
	
	printf("�ѽ���%d��%d��%d�ա�\n", pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday);
}
