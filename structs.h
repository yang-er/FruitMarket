#pragma once
#include <time.h>

/// <summary>����СƱ</summary>
typedef struct ticket {

	/// <summary>��ţ����0001-9999��</summary>
	short tid;

	/// <summary>����ʱ�䣨��&lt;time.h&gt;��</summary>
	time_t time;

	/// <summary>ˮ��������������warehouse��Ӧ��</summary>
	int amount[5];

	/// <summary>ˮ���������ࣨ��warehouse��Ӧ��</summary>
	int fruit;

	/// <summary>ˮ���������warehouse��Ӧ��</summary>
	int credit[5];

	/// <summary>��Ա���ţ�-1Ϊ�ֽ�</summary>
	short vipCard;

	/// <summary>�����ֽ� / ��Ա��ԭ���</summary>
	int given;

	/// <summary>�����ֽ� / ��Ա������� </summary>
	int left;

	/// <summary>�������һ���ڵ�</summary>
	struct ticket *next;

} ticket;

/// <summary>��Ʒ���</summary>
typedef struct stock {

	/// <summary>ˮ������</summary>
	char fruitName[21];

	/// <summary>��λ���ƣ��� / �� / ���ȣ�</summary>
	char tagName[21];

	/// <summary>�Ƿ񵥸�����</summary>
	bool isSingled;

	/// <summary>ʣ����</summary>
	int left;

	/// <summary>����������</summary>
	int sold;

	/// <summary>���ۣ���Ϊ��λ��</summary>
	int singlePrice;

	/// <summary>
	/// �������˶���Ǯ��
	/// </summary>
	int todayUsage;

	/// <summary>һ�ж��ٸ�</summary>
	int boxCount;

} stock;

/// <summary>��Ա���û�</summary>
typedef struct user {

	/// <summary>�ֿ���ǩ��</summary>
	char name[21];

	/// <summary>�û���ţ�0001-9999��</summary>
	short uid;

	/// <summary>�û�����Ϊ��λ��</summary>
	int balance;

	/// <summary>�����ܶ��Ϊ��λ��</summary>
	int todayUsage;

	/// <summary>�������һ���ڵ�</summary>
	struct user *next;

} user;
