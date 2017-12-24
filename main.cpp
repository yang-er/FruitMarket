#include "stdafx.h"
#include "scan.h"
#include "stock.h"
#include "user.h"
#include "ticket.h"

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
		LocalTime(&pDate, &pTicketRear->time);
		pDate.tm_min = 0;
		pDate.tm_hour = 0;
		pDate.tm_sec = 0;
		pTime = mktime(&pDate);

		// 输出时间
		printf("程序日期：%d年%d月%d日。\n",
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
	printf("保存数据完毕，正在退出. . . \n");
	sleep(500);
    return 0;
}

void menu_main()
{
	char op;
	while (true)
	{
		printf("====================\n");
		printf("|     水果商店     |\n");
		printf("====================\n");
		printf("|                  |\n");
		printf("|    1.库存管理    |\n");
		printf("|    2.用户管理    |\n");
		printf("|    3.购物记录    |\n");
		printf("|    4.第二天      |\n");
		printf("|    5.退出系统    |\n");
		printf("|                  |\n");
		printf("====================\n");
		printf("当前时间：%4d年%d月%d日。\n", pDate.tm_year + 1900, pDate.tm_mon + 1, pDate.tm_mday);
		op = ScanOption("请选择进入：", '1', '5');
		switch (op)
		{
			case '1': menu_stock(); break;
			case '2': menu_user(); break;
			case '3': menu_ticket(); break;
			case '4': push_date(); break;
			case '5': if (ScanBoolean("确定退出吗？(y/n)：")) return; break;
			default: break;
		}
		clear();
	}
}

void push_date()
{
	if (!ScanBoolean("直接进入下一天？(y/n)："))
	{
		SetCurrentDate();
	}
	else
	{
		ExportTickets();
		pDate.tm_mday += 1;
		pTime = mktime(&pDate);
	}
	
	printf("已进入%d年%d月%d日。\n", pDate.tm_year + 1900, pDate.tm_mon + 1, pDate.tm_mday);
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
