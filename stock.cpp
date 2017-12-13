#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "math.h"
#include "stock.h"

const char* pfStock = "stock.dat";
struct stock warehouse[5];

/// <summary>���ļ��м��ؿ����Ϣ</summary>
bool LoadStockFromFile()
{
	FILE *pFile;

	// �ļ����������ʼ��Ĭ��ֵ
	if (!file_exists(pfStock))
	{
		pFile = fopen(pfStock, "w");
		CheckFile(pFile, pfStock);
		fprintf(pFile, "ƻ�� ���� F 20 0 5 0 0\n");
		fprintf(pFile, "�㽶 �� T 20 0 5 0 0\n");
		fprintf(pFile, "���� �� T 20 0 5 0 0\n");
		fprintf(pFile, "��ݮ �� T 20 0 5 0 0\n");
		fprintf(pFile, "���� ���� F 20 0 5 0 0\n");
		fclose(pFile);
	}

	// ��ȡ�ļ�����
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

/// <summary>��ˮ�������Ϣ���浽�ļ�</summary>
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

/// <summary>�������ˮ���Ŀ��</summary>
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
		printf("|  ���ۣ�%d.%02d\n", warehouse[i].singlePrice / 100, warehouse[i].singlePrice % 100);
		if (warehouse[i].isSingled)
		{
			printf("|  ʣ�ࣺ%d\n", warehouse[i].left);
			printf("|  ������%d\n", warehouse[i].sold);
			printf("|  ������%d\n", warehouse[i].todayUsage);
			printf("|  һ�У�%d��\n", warehouse[i].boxCount);
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

/// <summary>����ĳһˮ���Ŀ��</summary>
bool AddStock()
{
	// ��ȷҪ������ˮ��
	printf("Ŀǰ��ˮ���У�");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i + 1, warehouse[i].fruitName);
	printf("\n");
	char op;
	ScanOption("������Ҫ������ˮ�����ࣺ", '1', '5', &op);
	int id = op - '1';
	printf("��ǰˮ���ĵ�λΪ��%s��\n", warehouse[id].tagName);

	// ��ȡ��������
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
		warehouse[id].left += (int)ceil(count * 20);
	}
	return true;
}

/// <summary>�޸�ĳһˮ��������</summary>
bool ModifyStock()
{
	// ��ȷҪ������ˮ��
	printf("Ŀǰ��ˮ���У�");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i + 1, warehouse[i].fruitName);
	printf("\n");
	char op;
	ScanOption("������Ҫ�޸ĵ�ˮ�����ࣺ", '1', '5', &op);
	int id = op - '1';
	printf("==================\n");
	printf("|\n");
	printf("|  ���ƣ�%s\n", warehouse[id].fruitName);
	printf("|  ��λ��%s\n", warehouse[id].tagName);
	printf("|  ���ۣ�%d.%02d\n", warehouse[id].singlePrice / 100, warehouse[id].singlePrice % 100);
	if (warehouse[id].isSingled)
		printf("|  һ�У�%d��\n", warehouse[id].sold);
	printf("|\n");
	printf("==================\n");
	printf("\n");

	// ��ȡ��������
	if (ScanBoolean("�Ƿ��޸����ƣ�(y/n)��"))
	{
		memset(warehouse[id].fruitName, 0x00, 21);
		ScanText("�����ƣ�", warehouse[id].fruitName, 20);
	}
	if (ScanBoolean("�Ƿ��޸ĵ�λ��(y/n)��"))
	{
		memset(warehouse[id].tagName, 0x00, 21);
		ScanText("��λ���ƣ�", warehouse[id].tagName, 20);
	}
	if (ScanBoolean("�Ƿ��޸ĵ��ۣ�(y/n)��"))
	{
		double p;
		ScanDouble("�µĵ��ۣ�", &p);
		warehouse[id].singlePrice = (int) floor(p * 100 + 0.5);
	}
	if (warehouse[id].isSingled && ScanBoolean("�Ƿ��޸�һ�еĸ�����(y/n)��"))
	{
		ScanInt("һ�и�����", &warehouse[id].boxCount);
	}
	return true;
}

/// <summary>����ֿ�ģʽ</summary>
void _stock()
{
	_clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    ˮ���ⷿ\n");
		printf("==================\n");
		printf("|\n");
		printf("|    1.��ⷿ\n");
		printf("|    2.����\n");
		printf("|    3.�޸�\n");
		printf("|    4.�˳�\n");
		printf("|\n");
		printf("==================\n");
		ScanOption("��ѡ����룺", '1', '6', &op);
		printf("\n");
		switch (op)
		{
		case '1':
			OutputStock();
			printf("\n�����������... ");
			rewind(stdin);
			getchar();
			rewind(stdin);
			_clear();
			break;
		case '2':
			AddStock();
			printf("������\n");
			_sleep(500);
			_clear();
			break;
		case '4':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
			break;
		case '3':
			ModifyStock();
			printf("����޸����\n");
			_sleep(500);
			_clear();
			break;
		}
		if (op == -52)
		{
			SaveStockToFile();
			_sleep(500);
			_clear();
			break;
		}
	}
}