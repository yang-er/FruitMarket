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

	/// <summary>
	/// ����
	/// </summary>
	struct ticket *next;

};

/// <summary>
/// ��Ʒ���
/// </summary>
struct stock {

	/// <summary>
	/// ˮ�����ơ�
	/// </summary>
	char fruitName[21];

	/// <summary>
	/// ��λ���ơ�
	/// </summary>
	char tagName[21];

	/// <summary>
	/// �Ƿ񵥸����ۡ�
	/// </summary>
	bool isSingled;

	/// <summary>
	/// ʣ���档
	/// </summary>
	int left;

	/// <summary>
	/// ��������
	/// </summary>
	int sold;

	/// <summary>
	/// ���ۡ�
	/// </summary>
	int singlePrice;

	/// <summary>
	/// �������˶���Ǯ��
	/// </summary>
	int todayUsage;

	/// <summary>
	/// һ�ж��ٸ���
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
