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
	printf("正在加载数据. . . ");
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	sleep(250);
	clear();
	_main_test();
	SaveUserToFile();
	SaveTicketToFile();
	SaveStockToFile();
	printf("保存数据完毕，正在退出. . . ");
	sleep(500);
    return 0;
}

void _main_test()
{
	char op;
	while (true)
	{
		printf("1.呵，杨良正  2.呵，杜维康  3.呵，徐英杰  4.呵，宗折翼 5.呵，吕游\n");
		op = ScanOption("请选择进入：", '1', '5');
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
			if (ScanBoolean("确定退出嘛(y/n)："))
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
