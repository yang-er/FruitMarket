#include "stdafx.h"
#include "structs.h"

/// <summary>
/// 从文件加载用户信息。
/// </summary>
struct user *LoadUserFromFile()
{
	return NULL;
}

/// <summary>
/// 将用户信息保存到文件。
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
	*/
}