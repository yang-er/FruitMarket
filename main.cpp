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
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	_main_test();
	SaveUserToFile();
	SaveTicketToFile();
	SaveStockToFile();
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
		printf("1.ºÇ£¬ÑîÁ¼Õı  2.ºÇ£¬¶ÅÎ¬¿µ  3.ºÇ£¬ĞìÓ¢½Ü  4.ºÇ£¬×ÚÕÛÒí\n");
		ScanOption("ÇëÑ¡Ôñ½øÈë£º", '1', '5', &op);
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
		case '4':
			if (ScanBoolean("È·¶¨ÍË³öÂï(y/n)£º"))
				op = -52;
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
