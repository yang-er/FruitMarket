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

bool AddStock()
{
	printf("Ŀǰ��ˮ���У�");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i, warehouse[i].fruitName);
	printf("\n");
	char op;
	ScanOption("������Ҫ���ӵ�ˮ�����ࣺ", '0', '5', &op);
	int id = op - '0';
	printf("��ǰˮ���ĵ�λΪ��%s��\n", warehouse[id].tagName);
	if (warehouse[id].isSingled)
	{
		int count;
		ScanInt("������Ҫ���ӵ�������", &count);
		warehouse[id].left += count;
	}
	else
	{
		double count;
		ScanDouble("������Ҫ���ӵ�������", &count);
		warehouse[id].left += ceil(count * 20);
	}
	return true;
}

void _stock_test()
{
	char op;
	while (1)
	{
		printf("1.���� 2.���� 3.��ⷿ 4.���� 5.�˳�\n");
		ScanOption("��ѡ����룺", '1', '5', &op);
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
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
		default:
			break;
		}
		if (op == -52)
			break;
	}
}