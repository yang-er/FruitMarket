#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "ticket.h"
#include "user.h"
#include "stock.h"

ticket *pTicketFront = NULL;
ticket *pTicketRear = NULL;
ticket *pTicketTemp = NULL;
const char *pfTicket = "ticket.dat";

ticket *FindTicket(short tid)
{
	ticket* temp;
	temp = pTicketFront;
	while (temp != NULL && temp->tid != tid)
		temp = temp->next;
	return temp;
}

void LoadTicketFromFile()
{
	return;
}

bool SaveTicketToFile()
{
	return false;
}

bool AddTicket()
{
	do {
		_alloc(pTicketTemp, ticket);

		// 确定小票编号
		bool bFlag = true;
		do {
			ScanShort("请输入序号：", &pTicketTemp->tid, false);
			bFlag = FindTicket(pTicketTemp->tid) != NULL;
			if (bFlag) printf("小票%04d已存在！\n", pTicketTemp->tid);
			if (bFlag && !ScanBoolean("是否更换号码？(y/n)："))
			{
				_free(pTicketTemp, ticket);
				pTicketTemp = NULL;
				bFlag = false;
			}
		} while (bFlag);
		
		if (pTicketTemp == NULL) continue;

		// 确定购买数量和总金额
		printf("以下不够买请输入0。");
		double c = 0;
		int d = 0, sum = 0;
		char msg[38];

		for (int i = 0; i < 5; i++)
		{
			sprintf(msg, "请输入%s购买数量：", warehouse[i].fruitName);
			if (warehouse[i].isSingled)
			{
				do { ScanInt(msg, &d); } while (d < 0 && printf("购买数量不合法！\n"));
				pTicketTemp->amount[i] = d;
				pTicketTemp->credit[i] = d * warehouse[i].singlePrice;
			}
			else
			{
				do { ScanDouble(msg, &c); } while (c < 0 && printf("购买数量不合法！\n"));
				pTicketTemp->amount[i] = cent(c);
				pTicketTemp->credit[i] = cent(c * warehouse[i].singlePrice);
			}
			sum += pTicketTemp->credit[i];
		}

		// 确定支付方式
		bFlag = true;
		do {

			// 会员卡 or 现金
			do {
				ScanShort("请输入会员卡号（现金为-1）：", &pTicketTemp->vipCard, true);
			} while (GetCardById(pTicketTemp->vipCard) == NULL && printf("没有找到该会员。\n"));

			if (pTicketTemp->vipCard == -1)
			{
				// 收现金
				bool bFlag = true;
				do {
					ScanInt("请输入收入现金数量：", &pTicketTemp->given);
					bFlag = pTicketTemp->given < sum;
					if (bFlag) printf("不能倒贴钱。\n");
					if (bFlag && !ScanBoolean("是否更换收入现金数量？(y/n)："))
					{
						_free(pTicketTemp, ticket);
						pTicketTemp = NULL;
						bFlag = false;
					}
				} while (bFlag);
				if (pTicketTemp == NULL) break;

				pTicketTemp->left = pTicketTemp->given - sum;
			}
			else
			{
				// 收会员卡
				bool bFlag = false;
				while (pUserTemp->balance < sum)
				{
					if (ScanBoolean("余额不足，是否立刻充值？(y/n)："))
					{
						ChargeInConsole(pTicketTemp->vipCard);
					}
					else
					{
						if (ScanBoolean("是否更换其他卡或使用现金购买？(y/n)："))
						{
							bFlag = true;
						}
						else
						{
							printf("放弃充值，购买失败，退出中. . . \n");
							_free(pTicketTemp, ticket);
							pTicketTemp = NULL;
						}
						break;
					}
				}
				if (bFlag) continue;
				if (pTicketTemp == NULL) break;
			}

		} while (bFlag);

		if (pTicketTemp == NULL) continue;
		
		ChargeToCard(pTicketTemp->vipCard, sum, false);
		pUserTemp = NULL;

		if (pTicketRear == NULL)
		{
			pTicketFront = pTicketTemp;
			pTicketRear = pTicketTemp;
		}
		else
		{
			pTicketRear->next = pTicketTemp;
			pTicketRear = pTicketTemp;
		}

		pTicketTemp = NULL;

	} while (ScanBoolean("是否继续新建订单？(y/n)："));
	
	return false;
}

void OutputTicket(ticket* ticket, bool isFull) 
{
	if (isFull)
	{
		printf("==============================================\n");
		printf("|                水果超市票据                |\n");
	}
	printf("==============================================\n");
	printf("|                                            |\n");
	printf("|  付款人：%10s  付款卡：%04d          |\n", "", 0);
	printf("|  付款方式：%6s    票据编号：%04d        |\n", "会员卡", 0);
	int calc = int(ticket->time - pTime);
	printf("|  订购时间：%04d年%-2d月%-2d日 %-2d:%02d            |\n", 
		pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday, calc / 3600, calc / 60 % 60);
	printf("|--------------------------------------------|\n");
	printf("|  # 商品名           单价    数量     金额  |\n");
	int sum = 0;
	double count = 0, credit = 0;
	for (int i = 0; i < 5; i++)
	{
		if (pTicketTemp->amount[i] == 0) continue;
		sum += pTicketTemp->credit[i];
		credit = dollar(pTicketTemp->credit[i]);
		count = dollar(pTicketTemp->amount[i] * (warehouse[i].isSingled ? 100 : 1));
		printf("|  %d %12s  %-7.2lf %-7.2lf %-8.2lf  |\n",
			i+1, warehouse[i].fruitName, credit / count, count, credit);
	}
	printf("|--------------------------------------------|\n");
	printf("|  合计                            %-8.2lf  |\n", dollar(sum));
	printf("|                                            |\n");
	printf("|  收款：%8.2lf      找零：%8.2lf        |\n", dollar(pTicketTemp->given), dollar(pTicketTemp->left));
	printf("|                                            |\n");
	if (isFull)
	{
		printf("|  1天退货保障  3天新鲜承诺   109店全院连锁  |\n");
		printf("|                                            |\n");
		printf("==============================================\n");
	}

}

void OutputAllTickets()
{
	printf("==============================================\n");
	printf("|                水果超市票据                |\n");
	pTicketTemp = pTicketFront->next;
	while (pTicketTemp != NULL)
	{
		OutputTicket(pTicketTemp, false);
		pTicketTemp = pTicketTemp->next;
	}
	printf("==============================================\n");
}

bool ModifyTicket(short tid)
{
	if (ScanBoolean("是否同时变动金额、库存等的改动？(y/n)："))
	{
		// TODO
	}
	else
	{
		// TODO
	}
	return false; 
}

bool DeleteTicket(short tid)
{
	if (ScanBoolean("是否撤销金额、库存等的改动？(y/n)："))
	{
		// TODO
	}
	else
	{
		// TODO
	}
	return false; 
}

void _ticket_test()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    小票系统\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.添加一张小票\n");
		printf("|   2.输出一张小票的信息\n");
		printf("|   3.按照号码查找小票\n");
		printf("|   4.修改小票内容\n");
		printf("|   5.删除小票\n");
		printf("|   6.查询大额购物信息\n");
		printf("|   7.查询某段时间内购物信息\n");
		printf("|   8.退出\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("请选择进入：", '1', '8');
		printf("\n");
		switch (op)
		{
		case '1':
			AddTicket();
			sleep(500);
			break;
		case '2':
			short tid;
			ScanShort("请输入购物单号：", &tid, false);
			pTicketTemp = FindTicket(tid);
			if (pTicketTemp == NULL)
			{
				printf("没有找到该购物记录。\n");
			}
			else
			{
				OutputTicket(pTicketTemp, true);
				pTicketTemp = NULL;
			}
			pause();
			break;
		case '3':
			pause();
			break;
		case '4':
			sleep(500);
			break;
		case '5':
			sleep(500);
			break;
		case '6':
			sleep(500);
			break;
		case '7':
			sleep(500);
			break;
		case '8':
			if (ScanBoolean("确定退出嘛(y/n)："))
				op = -52;
			break;
		default:
			break;
		}
		
		if (op == -52)
		{
			SaveTicketToFile();
			SaveUserToFile();
			SaveStockToFile();
			LoadStockFromFile();
			LoadUserFromFile();
			LoadTicketFromFile();
			sleep(500);
			clear();
			break;
		}
		clear();
	}
}