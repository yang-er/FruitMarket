#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

extern void _ticket_test();
extern void _main_test();

int main()
{
	SetCurrentDate();
	printf("���ڼ�������. . . ");
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	sleep(250);
	clear();
	_main_test();
	SaveUserToFile();
	SaveTicketToFile();
	SaveStockToFile();
	printf("����������ϣ������˳�. . . ");
	sleep(500);
    return 0;
}

void _main_test()
{
	char op;
	while (true)
	{
		printf("1.�ǣ�������  2.�ǣ���ά��  3.�ǣ���Ӣ��  4.�ǣ������� 5.�ǣ�����\n");
		op = ScanOption("��ѡ����룺", '1', '5');
		switch (op)
		{
		case '1':
			_stock();
			break;
		case '2':
			_user();
			break;
		case '3':
			_ticket_test();
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
