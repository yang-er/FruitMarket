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
			printf("�����ʼ��ʧ�ܣ������˳�. . . \n");
			exit(4);
		}
		fprintf(pFile, "ƻ�� ���� F 0 0 340 0 0\n");
		fprintf(pFile, "�㽶 �� T 0 0 110 0 4\n");
		fprintf(pFile, "���� �� T 0 0 1100 0 4\n");
		fprintf(pFile, "��ݮ ���� F 0 0 1277 0 0\n");
		fprintf(pFile, "���� ���� F 0 0 364 0 0\n");
		fclose(pFile);
	}

	// ��ȡ�ļ�����
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
			fprintf(stderr, "%s�ļ����ݱ��ƻ����޷�У��ͨ�����˳���. . . ", pfStock);
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
	} while (pFile == NULL && ScanBoolean("�ļ�stock.dat�޷��򿪣��Ƿ����ԣ�(y/n)��"));

	if (pFile == NULL)
	{
		printf("�����ļ����棬�������Ľ���������. . . \n");
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
	printf("|    ������\n");
	printf("==================\n");
	for (int i = 0; i < 5; i++)
	{
		printf("|\n");
		printf("|  ���ƣ�%s\n", warehouse[i].fruitName);
		printf("|  ��λ��%s\n", warehouse[i].tagName);
		printf("|  ���ۣ�%.2lf\n", dollar(warehouse[i].singlePrice));
		if (warehouse[i].isSingled)
		{
			printf("|  һ�У�%d��\n", warehouse[i].boxCount);
			printf("|  ʣ�ࣺ%d\n", warehouse[i].left);
			printf("|  ������%d\n", warehouse[i].sold);
		}
		else
		{
			printf("|  ʣ�ࣺ%.2lf\n", dollar(warehouse[i].left));
			printf("|  ������%.2lf\n", dollar(warehouse[i].sold));
		}
		printf("|  ����������%.2lf\n", dollar(warehouse[i].todayUsage));
		printf("|\n");
		printf("==================\n");
	}
}

bool AddStock()
{
	// ��ȷҪ������ˮ��
	printf("Ŀǰ��ˮ���У�");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i + 1, warehouse[i].fruitName);
	printf("\n");
	char op;
	op = ScanOption("������Ҫ������ˮ�����ࣺ", '1', '5');
	int id = op - '1';
	printf("��ǰˮ���ĵ�λΪ��%s��\n", warehouse[id].tagName);

	// ��ȡ��������
	if (warehouse[id].isSingled)
	{
		int count;
		ScanInt("������Ҫ���ӵ�������", &count);
		warehouse[id].left += count;
		if (warehouse[id].left > 1000 || warehouse[id].left <= 0)
		{
			printf("�����ˡ��Զ���������1000��\n");
			warehouse[id].left = 1000;
		}
	}
	else
	{
		double count;
		ScanDouble("������Ҫ���ӵ�������", &count);
		warehouse[id].left += cent(count);
		if (warehouse[id].left > 10000 || warehouse[id].left <= 0)
		{
			printf("�����ˡ��Զ���������100��\n");
			warehouse[id].left = 10000;
		}
	}
	return true;
}

bool ModifyStock()
{
	// ��ȷҪ������ˮ��
	printf("Ŀǰ��ˮ���У�");
	for (int i = 0; i < 5; i++)
		printf("%d.%s ", i + 1, warehouse[i].fruitName);
	printf("\n");
	char op = ScanOption("������Ҫ�޸ĵ�ˮ�����ࣺ", '1', '5');
	int id = op - '1';
	printf("==================\n");
	printf("|\n");
	printf("|  ���ƣ�%s\n", warehouse[id].fruitName);
	printf("|  ��λ��%s\n", warehouse[id].tagName);
	printf("|  ���ۣ�%.2lf\n", dollar(warehouse[id].singlePrice));
	if (warehouse[id].isSingled)
		printf("|  һ�У�%d��\n", warehouse[id].sold);
	printf("|\n");
	printf("==================\n");
	printf("\n");

	// ��ȡ��������
	if (ScanBoolean("�Ƿ��޸����ƣ�(y/n)��"))
		ScanText("�����ƣ�", warehouse[id].fruitName, 21);

	if (ScanBoolean("�Ƿ��޸ĵ�λ��(y/n)��"))
		ScanText("��λ���ƣ�", warehouse[id].tagName, 21);
	
	if (ScanBoolean("�Ƿ��޸ĵ��ۣ�(y/n)��"))
	{
		double p;
		ScanDouble("�µĵ��ۣ�", &p);
		warehouse[id].singlePrice = cent(p);
	}

	if (warehouse[id].isSingled && ScanBoolean("�Ƿ��޸�һ�еĸ�����(y/n)��"))
		ScanInt("һ�и�����", &warehouse[id].boxCount);

	return true;
}

void menu_stock()
{
	clear();
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
		op = ScanOption("��ѡ����룺", '1', '4');
		printf("\n");
		switch (op)
		{
		case '1': OutputStock(); _pause(); break;
		case '2': do { AddStock(); } while (ScanBoolean("�Ƿ������ӿ�棿(y/n)��")); printf("������\n"); break;
		case '3': ModifyStock(); printf("����޸���ϡ�\n"); break;
		case '4': if (ScanBoolean("ȷ���˳���(y/n)��")) op = -52; break;
		default: break;
		}

		// �˳�ʱ��������Ϣ
		if (op == -52)
		{
			SaveStockToFile();
			sleep(500);
			clear();
			break;
		}

		// ����Ļ
		sleep(500);
		clear();
	}
}
