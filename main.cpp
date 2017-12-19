#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

extern void menu_main();

int main()
{
	SetCurrentDate();
	printf("���ڼ�������. . . ");
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	sleep(250);
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
			printf("coming soon...\n");
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

}
