#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

struct user *user_list;

extern void _stock_test();
extern void _user_test();
extern void _ticket_test();
extern void _main_test();

int main()
{
	time_t p;
	struct tm*cur;
	time(&p);
	cur = localtime(&p);
	printf("Ŀǰʱ�䣺%s", asctime(cur));
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	_main_test();
#ifdef DEBUG
	system("pause");
#endif
    return 0;
}

void _main_test()
{
	char op;
	while (1)
	{
		printf("1.�ǣ�������  2.�ǣ���ά��  3.�ǣ���Ӣ��  4.�ǣ�������\n");
		ScanOption("��ѡ����룺", '1', '5', &op);
		switch (op)
		{
		case '1':
			_stock_test();
			break;
		case '2':
			_user_test();
			break;
		case '3':
			_ticket_test();
			break;
		case '4':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
		default:
			break;
		}
		if (op == -52)
			break;
	}
}
