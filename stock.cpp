#include "stdafx.h"
#include "structs.h"

const char* pfStock = "stock.dat";

bool LoadStockFromFile(struct stock warehouse[5])
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

bool SaveStockToFile(struct stock warehouse[5])
{
	FILE *pFile;
	pFile = fopen(pfStock, "w");
	CheckFile(pFile, pfStock);
	struct stock *pStock;
	for (int i = 0; i < 5; i++)
	{
		pStock = warehouse + i;
		fprintf(pFile, "%s %s %c %d %d %d %d %d",
			pStock->fruitName, pStock->tagName, pStock->isSingled ? 'T' : 'F',
			pStock->left, pStock->sold, pStock->singlePrice,
			pStock->todayUsage, pStock->boxCount);
	}
	fclose(pFile);
	return true;
}

void OutputStock(struct stock warehouse[5])
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

bool AddStock(struct stock fruit, int count)
{
	return false;
}

