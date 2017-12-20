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
	struct stat pStat;

	// 清空内存中的信息
	while (pTicketFront != NULL)
	{
		pTicketTemp = pTicketFront;
		pTicketFront = pTicketFront->next;
		pTicketTemp->next = NULL;
		_free(pTicketTemp, ticket);
	}
	pTicketRear = NULL;
	pTicketTemp = NULL;

	// 文件不存在的时候初始化为空数组
	if (stat(pfTicket, &pStat) == -1)
	{
		_alloc(pTicketTemp, ticket);
		pTicketFront = pTicketTemp;
		pTicketRear = pTicketTemp;
		pTicketTemp = NULL;
		return;
	}

	// 检测文件完整度
	if (pStat.st_size % sizeof(ticket) != 0)
		DataNotFulfilled(NULL, pfTicket);

	// 打开文件
	FILE *pFile = fopen(pfTicket, "r");
	CheckFile(pFile, pfTicket);
	for (int i = 0; i < pStat.st_size / sizeof(ticket); i++)
	{
		_alloc(pTicketTemp, ticket);
		fread(pTicketTemp, sizeof(ticket), 1, pFile);
		if (pTicketFront == NULL) pTicketFront = pTicketTemp;
		if (pTicketRear != NULL) pTicketRear->next = pTicketTemp;
		pTicketRear = pTicketTemp;
		pTicketTemp = NULL;
	}
	fclose(pFile);
	return;
}

bool SaveTicketToFile()
{
	FILE *pFile = fopen(pfTicket, "w+");
	CheckFile(pFile, pfTicket);
	while (pTicketFront != NULL)
	{
		pTicketTemp = pTicketFront;
		pTicketFront = pTicketFront->next;
		pTicketTemp->next = NULL;
		fwrite(pTicketTemp, sizeof(ticket), 1, pFile);
		_free(pTicketTemp, ticket);
	}
	pTicketRear = NULL;
	pTicketTemp = NULL;
	fclose(pFile);
	return true;
}

// 释放并结束
#define doClean(p) do { \
			_free(pTicketTemp, ticket); \
			pTicketTemp = NULL; \
			return p; \
		} while (false)
#pragma warning (disable: 4003)

static bool payOne(int sum)
{
	// 会员卡 or 现金
	bool bContinue;
	do {
		ScanShort("请输入会员卡号（现金为-1）：", &pTicketTemp->vipCard, true);
		pUserTemp = GetCardById(pTicketTemp->vipCard);
	} while (pUserTemp == NULL && printf("没有找到该会员。\n"));

	// 收现金
	if (pTicketTemp->vipCard == -1)
	{
		double c;
		do {
			ScanDouble("请输入收入现金数量：", &c);
			pTicketTemp->given = cent(c);
			bContinue = pTicketTemp->given < sum;
			if (bContinue) printf("不能倒贴钱。\n");
			if (bContinue && !ScanBoolean("是否更换收入现金数量？(y/n)：")) doClean(false);
		} while (bContinue);
	}
	// 收会员卡
	else
	{
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
					return true;
				}
				else
				{
					printf("放弃充值，购买失败，退出中. . . \n");
					doClean(false);
				}
				break;
			}
		}
		pTicketTemp->given = pUserTemp->balance;
	}

	return false;
}

static void addOne()
{
	_alloc(pTicketTemp, ticket);
	// 确定小票编号
	pTicketTemp->tid = pTicketRear->tid + 1;

	// 确定购买时间
	pTicketTemp->time = ScanTime("请输入下单时间：");

	// 确定购买数量和总金额
	printf("以下不够买请输入0。\n");
	double c = 0;
	int d = 0, sum = 0;
	char msg[70];
	for (int i = 0; i < 5; i++)
	{
		if (warehouse[i].isSingled)
		{
			sprintf(msg, "请输入%s购买数量（%.2lf元/%s，剩余%d，一盒%d个）：",
				warehouse[i].fruitName, dollar(warehouse[i].singlePrice), warehouse[i].tagName, warehouse[i].left, warehouse[i].boxCount);
			do { ScanInt(msg, &d); } while ((d < 0 || d > warehouse[i].left) && printf("购买数量不合法！\n"));
			pTicketTemp->amount[i] = d;
			pTicketTemp->credit[i] = d * warehouse[i].singlePrice;
		}
		else
		{
			sprintf(msg, "请输入%s购买数量（%.2lf元/%s，剩余%.2lf）：",
				warehouse[i].fruitName, dollar(warehouse[i].singlePrice), warehouse[i].tagName, dollar(warehouse[i].left));
			do { ScanDouble(msg, &c); } while ((c < 0 || c > dollar(warehouse[i].left)) && printf("购买数量不合法！\n"));
			pTicketTemp->amount[i] = cent(c);
			pTicketTemp->credit[i] = int(c * warehouse[i].singlePrice);
		}
		sum += pTicketTemp->credit[i];
	}

	// 支付
	printf("将收取%.2lf元。\n", dollar(sum));
	while (payOne(sum));
	if (pTicketTemp == NULL) return;
	pTicketTemp->left = pTicketTemp->given - sum;
	ChargeToCard(pTicketTemp->vipCard, sum, false);
	pUserTemp = NULL;
	for (int i = 0; i < 5; i++)
	{
		warehouse[i].left -= pTicketTemp->amount[i];
		warehouse[i].sold += pTicketTemp->amount[i];
		warehouse[i].todayUsage += pTicketTemp->credit[i];
	}

	// 将订单加入队列
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

	OutputTicket(pTicketTemp, true);
	pTicketTemp = NULL;
}

#undef doClean

bool AddTicket()
{
	do {
		addOne();
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
	if (ticket->vipCard != -1)
	{
		pUserTemp = GetCardById(ticket->vipCard);
		if (pUserTemp == NULL)
			printf("|  付款人：已删除      付款卡：----          |\n");
		else
			printf("|  付款人：%-10s  付款卡：%04d          |\n", pUserTemp->name, pUserTemp->uid);
		pUserTemp = NULL;
	}
	printf("|  付款方式：%s    票据号：%04d          |\n", ticket->vipCard == -1 ? "现金  " : "会员卡", ticket->tid);
	printf("|                                            |\n");
	int calc = int(ticket->time - pTime);
	printf("|  订购时间：%04d年%2d月%2d日 %2d:%02d            |\n", 
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
		printf("|  %d %-12s  %7.2lf %7.2lf %8.2lf  |\n",
			i+1, warehouse[i].fruitName, credit / count, count, credit);
	}
	printf("|--------------------------------------------|\n");
	printf("|  合计                            %8.2lf  |\n", dollar(sum));
	printf("|                                            |\n");
	if (ticket->vipCard == -1)
		printf("|  收款：%8.2lf      找零：%8.2lf        |\n", dollar(pTicketTemp->given), dollar(pTicketTemp->left));
	else
		printf("|  原有：%8.2lf      余额：%8.2lf        |\n", dollar(pTicketTemp->given), dollar(pTicketTemp->left));
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
	// 临时变量
	double dbTemp;

	// 开始时间
	time_t ptStart = pTime;
	if (ScanBoolean("是否选择开始时间？(y/n)："))
		ptStart = ScanTime("输入开始的时间：");

	// 结束时间
	time_t ptEnd = pTime + 86341;
	if (ScanBoolean("是否选择结束时间？(y/n)："))
		ptEnd = ScanTime("输入结束的时间：");
	if (ptStart >= ptEnd) ptEnd = pTime + 86341;

	// 最低消费
	int crMin = 0;
	if (ScanBoolean("是否过滤最低消费？(y/n)："))
	{
		ScanDouble("请输入最低消费金额：", &dbTemp);
		if (dbTemp >= 0) crMin = cent(dbTemp);
	}

	// 最高消费
	int crMax = -1;
	if (ScanBoolean("是否过滤最高消费？(y/n)："))
	{
		ScanDouble("请输入最高消费金额：", &dbTemp);
		if (dbTemp > 0) crMax = cent(dbTemp);
		if (crMax < crMin) crMax = -1;
	}

	// 输出符合条件的小票
	printf("==============================================\n");
	printf("|                水果超市票据                |\n");
	pTicketTemp = pTicketFront->next;
	while (pTicketTemp != NULL)
	{
		int usage = pTicketTemp->given - pTicketTemp->left;
		if ((pTicketTemp->time >= ptStart) && (pTicketTemp->time <= ptEnd)
				&& (usage >= crMin) && (crMax == -1 || usage <= crMax))
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
		pTicketTemp = FindTicket(tid);
		if (pTicketTemp == NULL)
		{
			printf("单号%04hd不存在！\n", tid);
			return false;
		}
		if (ScanBoolean("是否修改购物时间？(y/n)："))
		{
			pTicketTemp->time = ScanTime("请输入新下单时间：");
		}
		pTicketTemp = NULL;
		return true;
	}
	return false; 
}

bool DeleteTicket(short tid)
{
	// 找到小票的前一个节点
	pTicketTemp = pTicketFront;
	while (pTicketTemp->next != NULL && pTicketTemp->next->tid != tid)
		pTicketTemp = pTicketTemp->next;
	if (pTicketTemp->next == NULL)
	{
		printf("单号%04hd不存在！\n", tid);
		pTicketTemp = NULL;
		return false;
	}

	ticket *temp = pTicketTemp->next;
	pTicketTemp->next = temp->next;

	if (ScanBoolean("是否立刻撤销金额、库存等的改动？(y/n)："))
	{
		int credit = 0;

		// 消除库存影响
		for (int i = 0; i < 5; i++)
		{
			warehouse[i].left += temp->amount[i];
			warehouse[i].sold -= temp->amount[i];
			credit += temp->credit[i];
		}

		// 消除余额影响
		if (pTicketTemp->vipCard == -1)
		{
			pUserTemp = GetCardById(temp->vipCard);
			if (pUserTemp == NULL || !ChargeToCard(temp->vipCard, 0, true))
			{
				printf("无法返回到卡内，请退现金%.2lf元。", dollar(credit));
				pUserTemp = NULL;
			}
		}

	}

	_free(temp, ticket);
	pTicketTemp = NULL;
	return true;
}

void ExportTickets()
{
	// 生成文件名
	char pFileName[30];
	sprintf(pFileName, "%04d-%d-%d 导出消费记录.csv",
		pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday);

	// 打开文件
	FILE *pFile;
	do {
		pFile = fopen(pFileName, "w+");
		if (pFile == NULL)
		{
			printf("文件%s操作失败。\n", pFileName);
			if (ScanBoolean("是否重试？(y/n)：")) continue;
		}
		break;
	} while (true);
	if (pFile == NULL) return;

	// 打印表头
	fprintf(pFile, "票号,时间,付款人,卡号,合计,收款,找零");
	for (int i = 0; i < 5; i++)
	{
		fprintf(pFile, ",%s数量,%s金额", warehouse[i].fruitName, warehouse[i].fruitName);
	}
	fprintf(pFile, "\n");

	// 打印每条记录
	pTicketTemp = pTicketFront->next;
	user *puser;
	int calc;
	while (pTicketTemp != NULL)
	{
		if (pTicketTemp->time < pTime || pTicketTemp->time > pTime + 86399)
		{
			pTicketTemp = pTicketTemp->next;
			continue;
		}
		calc = int(pTicketTemp->time - pTime);
		fprintf(pFile, "%04d,%d:%02d,", pTicketTemp->tid, calc / 3600, calc / 60 % 60);
		puser = GetCardById(pTicketTemp->vipCard);
		if (puser == NULL) fprintf(pFile, "已删除,0000,");
		else fprintf(pFile, "%s,%04d,", puser->name, puser->uid);
		fprintf(pFile, "%.2lf,%.2lf,%.2lf",
			dollar(pTicketTemp->given - pTicketTemp->left),
			dollar(pTicketTemp->given), dollar(pTicketTemp->left));
		for (int i = 0; i < 5; i++)
			if (warehouse[i].isSingled)
				fprintf(pFile, ",%d,%.2lf", pTicketTemp->amount[i], dollar(pTicketTemp->credit[i]));
			else
				fprintf(pFile, ",%.2lf,%.2lf", dollar(pTicketTemp->amount[i]), dollar(pTicketTemp->credit[i]));
		fprintf(pFile, "\n");
		pTicketTemp = pTicketTemp->next;
	}

	// 结束打印
	fclose(pFile);
	printf("记录已导出到“%s”。\n", pFileName);

}

void menu_ticket()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    小票系统\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.添加记录\n");
		printf("|   2.查找票号\n");
		printf("|   3.列出所有\n");
		printf("|   4.修改记录\n");
		printf("|   5.删除记录\n");
		printf("|   6.导出信息\n");
		printf("|   7.退出\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("请选择进入：", '1', '7');
		printf("\n");
		switch (op)
		{
		case '1': AddTicket(); break;
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
		case '3': OutputAllTickets(); pause(); break;
		case '4': short i0; ScanShort("请输入单号:", &i0, false); ModifyTicket(i0); break;
		case '5': short i; ScanShort("请输入单号：", &i, false); DeleteTicket(i); break;
		case '6': ExportTickets(); break;
		case '7': if (ScanBoolean("确定退出嘛(y/n)：")) op = -52; break;
		default: break;
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

		sleep(500);
		clear();
	}
}