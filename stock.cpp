#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "stock.h"

const char* pfStock = "stock.dat";
stock warehouse[5];

bool LoadStockFromFile()
{
	FILE *pFile;
	if(OpenFile(&pFile, pfStock, 1) == 0)
	{
		pFile = fopen(pfStock, "w");
		if (pFile == NULL)
		{
			printf("程序初始化失败，正在退出. . . \n");
			exit(4);
		}
		fprintf(pFile, "苹果 公斤 F 0 0 340 0 0\n");
		fprintf(pFile, "香蕉 根 T 0 0 110 0 4\n");
		fprintf(pFile, "柚子 个 T 0 0 1100 0 4\n");
		fprintf(pFile, "草莓 公斤 F 0 0 1277 0 0\n");
		fprintf(pFile, "梨子 公斤 F 0 0 364 0 0\n");
		fclose(pFile);
	}

	// 读取文件内容
	stock *pStock;
	char isSingle;
	int pFlag;
	for (int i = 0; i < 5; i++)
	{
		pStock = warehouse + i;
		pFlag = fscanf(pFile, "%s %s %c %d %d %d %d %d",
			pStock->fruitName, pStock->tagName, &isSingle,
			&pStock->left, &pStock->sold, &pStock->singlePrice,
			&pStock->todayUsage, &pStock->boxCount);
		if (pFlag != 8)
		{
			fprintf(stderr, "%s文件数据被破坏！无法校验通过，退出中. . . ", pfStock);
			sleep(5000);
			exit(4);
		}
		pStock->isSingled = (isSingle == 'T');
	}
	fclose(pFile);
	return true;
}

bool SaveStockToFile()
{
	FILE *pFile;
	do {
		pFile = fopen(pfStock, "w+");
	} while (pFile == NULL && ScanBoolean("文件stock.dat无法打开，是否重试？(y/n)："));

	if (pFile == NULL)
	{
		printf("放弃文件保存，所做更改将不被保存. . . \n");
		sleep(1000);
		return false;
	}

	stock *pStock;
	for (int i = 0; i < 5; i++)
	{
		pStock = warehouse + i;
		fprintf(pFile, "%s %s %c %d %d %d %d %d\n",
			pStock->fruitName, pStock->tagName, pStock->isSingled ? 'T' : 'F',
			pStock->left, pStock->sold, pStock->singlePrice,
			pStock->todayUsage, pStock->boxCount);
	}
	fclose(pFile);
	return true;
}

void OutputStock()
{
	flush_data();
	printf("==================\n");
	printf("|    库存管理\n");
	printf("==================\n");
	for (int i = 0; i < 5; i++)
	{
		printf("|\n");
		printf("|  名称：%s\n", warehouse[i].fruitName);
		printf("|  单位：%s\n", warehouse[i].tagName);
		printf("|  单价：%.2lf\n", dollar(warehouse[i].singlePrice));
		if (warehouse[i].isSingled)
		{
			printf("|  一盒：%d个\n", warehouse[i].boxCount);
			printf("|  剩余：%d\n", warehouse[i].left);
			printf("|  卖出：%d\n", warehouse[i].sold);
		}
		else
		{
			printf("|  剩余：%.2lf\n", dollar(warehouse[i].left));
			printf("|  卖出：%.2lf\n", dollar(warehouse[i].sold));
		}
		printf("|  已卖出：￥%.2lf\n", dollar(warehouse[i].todayUsage));
		printf("|\n");
		printf("==================\n");
	}
}

bool AddStock()
{
	// 明确要操作的水果
	printf("目前的水果有：");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i + 1, warehouse[i].fruitName);
	printf("\n");
	char op;
	op = ScanOption("请输入要进货的水果种类：", '1', '5');
	int id = op - '1';
	printf("当前水果的单位为：%s。\n", warehouse[id].tagName);

	// 获取进货数量
	if (warehouse[id].isSingled)
	{
		int count;
		ScanInt("请输入要增加的数量：", &count);
		warehouse[id].left += count;
		if (warehouse[id].left > 1000 || warehouse[id].left <= 0)
		{
			printf("爆仓了。自动将库存减到1000。\n");
			warehouse[id].left = 1000;
		}
	}
	else
	{
		double count;
		ScanDouble("请输入要增加的数量：", &count);
		warehouse[id].left += cent(count);
		if (warehouse[id].left > 10000 || warehouse[id].left <= 0)
		{
			printf("爆仓了。自动将库存减到100。\n");
			warehouse[id].left = 10000;
		}
	}
	return true;
}

bool ModifyStock()
{
	// 明确要操作的水果
	printf("目前的水果有：");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i + 1, warehouse[i].fruitName);
	printf("\n");
	char op = ScanOption("请输入要修改的水果种类：", '1', '5');
	int id = op - '1';
	printf("==================\n");
	printf("|\n");
	printf("|  名称：%s\n", warehouse[id].fruitName);
	printf("|  单位：%s\n", warehouse[id].tagName);
	printf("|  单价：%.2lf\n", dollar(warehouse[id].singlePrice));
	if (warehouse[id].isSingled)
		printf("|  一盒：%d个\n", warehouse[id].sold);
	printf("|\n");
	printf("==================\n");
	printf("\n");

	// 获取进货数量
	if (ScanBoolean("是否修改名称？(y/n)："))
		ScanText("新名称：", warehouse[id].fruitName, 21);

	if (ScanBoolean("是否修改单位？(y/n)："))
		ScanText("单位名称：", warehouse[id].tagName, 21);
	
	if (ScanBoolean("是否修改单价？(y/n)："))
	{
		double p;
		ScanDouble("新的单价：", &p);
		warehouse[id].singlePrice = cent(p);
	}

	if (warehouse[id].isSingled && ScanBoolean("是否修改一盒的个数？(y/n)："))
		ScanInt("一盒个数：", &warehouse[id].boxCount);

	return true;
}

void menu_stock()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    水果库房\n");
		printf("==================\n");
		printf("|\n");
		printf("|    1.查库房\n");
		printf("|    2.进货\n");
		printf("|    3.修改\n");
		printf("|    4.退出\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("请选择进入：", '1', '4');
		printf("\n");
		switch (op)
		{
		case '1': OutputStock(); _pause(); break;
		case '2': do { AddStock(); } while (ScanBoolean("是否继续添加库存？(y/n)：")); printf("添加完毕\n"); break;
		case '3': ModifyStock(); printf("库存修改完毕。\n"); break;
		case '4': if (ScanBoolean("确定退出吗？(y/n)：")) op = -52; break;
		default: break;
		}

		// 退出时保存库存信息
		if (op == -52)
		{
			SaveStockToFile();
			sleep(500);
			clear();
			break;
		}

		// 清屏幕
		sleep(500);
		clear();
	}
}
