#pragma once
#include <time.h>

/// <summary>
/// ����СƱ
/// </summary>
struct ticket {

	/// <summary>
	/// ��ţ����0001-9999��
	/// </summary>
	short tid;

	/// <summary>
	/// ����ʱ�䡣
	/// </summary>
	time_t time;

	/// <summary>
	/// ˮ�����ࡣ
	/// </summary>
	int fid;

	/// <summary>
	/// ˮ�����ࡣ
	/// </summary>
	int amount;

	/// <summary>
	/// ��Ա���ţ�-1Ϊ�ֽ�
	/// </summary>
	short vipCard;

	/// <summary>
	/// �����ֽ�
	/// </summary>
	int given;

	/// <summary>
	/// �����ֽ�
	/// </summary>
	int left;

};

/// <summary>
/// ��Ʒ���
/// </summary>
struct stock {

	/// <summary>
	/// �û���ţ�0001-999988��
	/// </summary>
	char fruitName[21];

	/// <summary>
	/// �û���ţ�0001-9999666��
	/// </summary>
	char tagName[21];

	/// <summary>
	/// �û���ţ�0001-9999��
	/// 1234567889
	/// </summary>
	bool isSingled;

	/// <summary>
	/// �û���ţ�0001-9999��
	/// </summary>
	int left;

	/// <summary>
	/// �û���ţ�0001-9999��
	/// </summary>
	int sold;

	/// <summary>
	/// �û���ţ�0001-9999��
	/// </summary>
	int singlePrice;

	/// <summary>
	/// ���컨�˶���Ǯ��
	/// </summary>
	int todayUsage;

	/// <summary>
	/// �û���ţ�0001-9999��
	/// </summary>
	int boxCount;

};

/// <summary>
/// ��Ա���û�
/// </summary>
struct user {

	/// <summary>
	/// �ֿ���ǩ����
	/// </summary>
	char name[21];

	/// <summary>
	/// �û���ţ�0001-9999��
	/// </summary>
	short uid;

	/// <summary>
	/// �û�����λ���֡�
	/// </summary>
	int balance;

	/// <summary>
	/// ���컨�˶���Ǯ��
	/// </summary>
	int todayUsage;

	/// <summary>
	/// �����е���һ���ڵ㡣
	/// </summary>
	struct user *next;

};
