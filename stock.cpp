#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "math.h"

const char* pfStock = "stock.dat";
extern struct stock warehouse[5];

bool LoadStockFromFile()
{
	FILE *pFile;
	if (!file_exists(pfStock))
	{
		pFile = fopen(pfStock, "w");
		CheckFile(pFile, pfStock);
		fprintf(pFile, "苹果 元/斤 F 20 0 5 0 0\n");
		fprintf(pFile, "香蕉 根 T 20 0 5 0 0\n");
		fprintf(pFile, "柚子 个 T 20 0 5 0 0\n");
		fprintf(pFile, "蓝莓 串 T 20 0 5 0 0\n");
		fprintf(pFile, "梨子 元/斤 F 20 0 5 0 0\n");
		fclose(pFile);
	}
	pFile = fopen(pfStock, "r");
	CheckFile(pFile, pfStock);
	struct stock *pStock;
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
			DataNotFulfilled(pFile, pfStock);
		pStock->isSingled = (isSingle == 'T');
	}
	fclose(pFile);
	return true;
}

bool SaveStockToFile()
{
	FILE *pFile;
	pFile = fopen(pfStock, "w");
	CheckFile(pFile, pfStock);
	struct stock *pStock;
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
	printf("==================\n");
	printf("|    库存管理\n");
	printf("==================\n");
	for (int i = 0; i < 5; i++)
	{
		printf("|\n");
		printf("|  名称：%s\n", warehouse[i].fruitName);
		printf("|  单位：%s\n", warehouse[i].tagName);
		if (warehouse[i].isSingled)
		{
			printf("|  剩余：%d\n", warehouse[i].left);
			printf("|  卖出：%d\n", warehouse[i].sold);
			printf("|  今销：%d\n", warehouse[i].todayUsage);
			printf("|  一盒：%d\n", warehouse[i].sold);
		}
		else
		{
			printf("|  剩余：%.2lf\n", warehouse[i].left / 20.0);
			printf("|  卖出：%.2lf\n", warehouse[i].sold / 20.0);
			printf("|  今销：%.2lf\n", warehouse[i].todayUsage / 20.0);
		}
		printf("|\n");
		printf("==================\n");
	}
}

bool AddStock()
{
	printf("目前的水果有：");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i, warehouse[i].fruitName);
	printf("\n");
	char op;
	ScanOption("请输入要增加的水果种类：", '0', '5', &op);
	int id = op - '0';
	printf("当前水果的单位为：%s。\n", warehouse[id].tagName);
	if (warehouse[id].isSingled)
	{
		int count;
		ScanInt("请输入要增加的数量：", &count);
		warehouse[id].left += count;
	}
	else
	{
		double count;
		ScanDouble("请输入要增加的数量：", &count);
		warehouse[id].left += ceil(count * 20);
	}
	return true;
}

void _stock_test()
{
	char op;
	while (1)
	{
		printf("1.保存 2.加载 3.查库房 4.进货 5.退出\n");
		ScanOption("请选择进入：", '1', '5', &op);
		switch (op)
		{
		case '1':
			SaveStockToFile();
			break;
		case '2':
			LoadStockFromFile();
			break;
		case '3':
			OutputStock();
			break;
		case '4':
			AddStock();
			break;
		case '5':
			if (ScanBoolean("确定退出嘛(y/n)："))
				op = -52;
		default:
			break;
		}
		if (op == -52)
			break;
	}
}