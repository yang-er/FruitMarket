#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "math.h"
FILE *file;
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
	if ((file = fopen("user.dat", "w+")) == NULL)
	{
		printf("打开失败\n");
		exit(0);
	}
	
	return false;
}

bool ChargeToCard(int uid, int credit, bool isAdd)
{
	return false;
}

struct user *createCard()
{
	struct user *head = NULL;
	struct user *p1, *p2 = NULL;
	int i = 1, j = 1;
	while (j != 0)
	{
		p1 = (struct user *)malloc(sizeof(struct user));
		ScanText("请输入持卡人签名:", p1->name, 21);
		ScanShort("请输入编号:", &p1->uid);
		ScanInt("请输入会员卡余额:", &p1->balance);
		ScanInt("请输入当日开销:", &p1->todayUsage);
		if (i == 1)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		i++;
			ScanInt("请输入是否继续保存:1.是,0.否", &j);
	}
	p2->next = NULL;
	return head;
}

bool CrashCard(int uid)
{
	return false;
}

bool ListVip(struct user* current)
{
	printf("==================\n");
	printf("|    会员信息\n");
	printf("==================\n");
	printf("\n");
	printf("会员姓名:%s\n", current->name);
	printf("会员卡号:%d\n", current->uid);
	printf("用户余额:%d\n", current->balance);
	printf("今日开销:%d\n", current->todayUsage);
	return false;
}

bool ListAllVips(struct user* vipHead)
{
	while (vipHead != NULL)
	{
		ListVip(vipHead);
		vipHead = vipHead->next;
	}
	return false;
}

void printvip(struct user* vipHead) {
	struct user *p1=NULL;
	short i;
	bool flag = false;
	ScanShort("请输入会员卡号", &i);
	 do{
		 p1 = vipHead;
		vipHead = vipHead->next;
	 } while (vipHead != NULL && p1->uid != i);
	if (p1->uid == i)
		flag = true;
	if (!flag)
		printf("没有找到\n");
	else
		ListVip(p1);
}
void inputuid()
{
	short i;
	ScanShort("请输入会员卡号:", &i);
	CrashCard(i);
}
void _user_test()
{
	struct user *p=NULL;
	char op;
	while (1)
	{
	printf("1.创建单个会员并保存 2.加载会员信息 3.加载单个会员 4.加载全部会员 5.删除单个会员 6.退出\n");
	ScanOption("请选择进入：", '1', '6', &op);
	switch (op)
	{
	case '1':
		p=createCard();
		break;
	case '2':
		LoadUserFromFile();
		break;
	case '3':
		printvip(p);
		break;
	case '4':
		ListAllVips(p);
		break;
	case '5':
		inputuid();
		break;
	case '6':
		if (ScanBoolean("确定退出嘛(y/n)："))
			op = -52;
	default:
		break;
}
if (op == -52)
break;
	}
}
