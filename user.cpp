#include "stdafx.h"
#include "structs.h"

/// <summary>
/// ���ļ������û���Ϣ��
/// </summary>
struct user *LoadUserFromFile()
{
	return NULL;
}

/// <summary>
/// ���û���Ϣ���浽�ļ���
/// </summary>
bool SaveUserToFile(struct user* vip)
{
	return false;
}

bool ChargeToCard(int uid, int credit, bool isAdd)
{
	return false;
}

int CreateCard(int credit, char name[21])
{
	return 0;
}

bool CrashCard(int uid)
{
	return false;
}

bool ListVip(struct user* current)
{
	return false;
}

bool ListAllVips(struct user* vipHead)
{
	return false;
}

void _user_test()
{
	/*
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
	*/
}