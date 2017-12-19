#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

extern void menu_main();

int main()
{
	SetCurrentDate();
	printf("正在加载数据. . . ");
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	sleep(250);
	clear();
	menu_main();
	SaveUserToFile();
	SaveTicketToFile();
	SaveStockToFile();
	printf("保存数据完毕，正在退出. . . ");
	sleep(500);
    return 0;
}

void menu_main()
{
	char op;
	while (true)
	{
		printf("1.呵，杨良正  2.呵，杜维康  3.呵，徐英杰  4.呵，宗折翼 5.呵，吕游\n");
		op = ScanOption("请选择进入：", '1', '5');
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
