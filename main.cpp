#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

extern void menu_main();

int main()
{
	printf("正在加载数据. . . \n");
	LoadStockFromFile();
	LoadTicketFromFile();
	LoadUserFromFile();
	if (pTicketFront == pTicketRear)
	{
		SetCurrentDate();
	}
	else
	{
		// 设置pTime和pCurrentDate
		pCurrentDate = localtime(&pTicketRear->time);
		pCurrentDate->tm_min = 0;
		pCurrentDate->tm_hour = 0;
		pCurrentDate->tm_sec = 0;
		pTime = mktime(pCurrentDate);

		// 输出时间
		printf("程序日期：%d年%d月%d日。\n",
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
			PushDate();
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
	ExportTickets();
	pCurrentDate->tm_mday += 1;
	pTime = mktime(pCurrentDate);
	for (int i = 0; i < 5; i++)
		warehouse[i].todayUsage = 0;
	for (pUserTemp = pUserFront; pUserTemp != NULL; pUserTemp = pUserTemp->next)
		pUserTemp->todayUsage = 0;
	
	printf("已进入%d年%d月%d日。\n", pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday);
}
