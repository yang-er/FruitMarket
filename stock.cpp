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
		fprintf(pFile, "ƻ�� Ԫ/�� F 20 0 5 0 0\n");
		fprintf(pFile, "�㽶 �� T 20 0 5 0 0\n");
		fprintf(pFile, "���� �� T 20 0 5 0 0\n");
		fprintf(pFile, "��ݮ �� T 20 0 5 0 0\n");
		fprintf(pFile, "���� Ԫ/�� F 20 0 5 0 0\n");
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
	printf("|    ������\n");
	printf("==================\n");
	for (int i = 0; i < 5; i++)
	{
		printf("|\n");
		printf("|  ���ƣ�%s\n", warehouse[i].fruitName);
		printf("|  ��λ��%s\n", warehouse[i].tagName);
		if (warehouse[i].isSingled)
		{
			printf("|  ʣ�ࣺ%d\n", warehouse[i].left);
			printf("|  ������%d\n", warehouse[i].sold);
			printf("|  ������%d\n", warehouse[i].todayUsage);
			printf("|  һ�У�%d\n", warehouse[i].sold);
		}
		else
		{
			printf("|  ʣ�ࣺ%.2lf\n", warehouse[i].left / 20.0);
			printf("|  ������%.2lf\n", warehouse[i].sold / 20.0);
			printf("|  ������%.2lf\n", warehouse[i].todayUsage / 20.0);
		}
		printf("|\n");
		printf("==================\n");
	}
}

bool AddStock(struct stock fruit, int count)
{
	return false;
}

