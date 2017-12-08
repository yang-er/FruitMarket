#pragma once
#include <time.h>

/// <summary>
/// 购物小票
/// </summary>
struct ticket {

	/// <summary>
	/// 序号，编号0001-9999。
	/// </summary>
	short tid;

	/// <summary>
	/// 购物时间。
	/// </summary>
	time_t time;

	/// <summary>
	/// 水果种类。
	/// </summary>
	int fid;

	/// <summary>
	/// 水果种类。
	/// </summary>
	int amount;

	/// <summary>
	/// 会员卡号，-1为现金。
	/// </summary>
	short vipCard;

	/// <summary>
	/// 收入现金。
	/// </summary>
	int given;

	/// <summary>
	/// 找零现金。
	/// </summary>
	int left;

	/// <summary>
	/// 链表。
	/// </summary>
	struct ticket *next;

};

/// <summary>
/// 商品库存
/// </summary>
struct stock {

	/// <summary>
	/// 水果名称。
	/// </summary>
	char fruitName[21];

	/// <summary>
	/// 单位名称。
	/// </summary>
	char tagName[21];

	/// <summary>
	/// 是否单个出售。
	/// </summary>
	bool isSingled;

	/// <summary>
	/// 剩余库存。
	/// </summary>
	int left;

	/// <summary>
	/// 总卖出。
	/// </summary>
	int sold;

	/// <summary>
	/// 单价。
	/// </summary>
	int singlePrice;

	/// <summary>
	/// 今天卖了多少钱。
	/// </summary>
	int todayUsage;

	/// <summary>
	/// 一盒多少个。
	/// </summary>
	int boxCount;

};

/// <summary>
/// 会员卡用户
/// </summary>
struct user {

	/// <summary>
	/// 持卡人签名。
	/// </summary>
	char name[21];

	/// <summary>
	/// 用户编号，0001-9999。
	/// </summary>
	short uid;

	/// <summary>
	/// 用户余额，单位：分。
	/// </summary>
	int balance;

	/// <summary>
	/// 今天花了多少钱。
	/// </summary>
	int todayUsage;

	/// <summary>
	/// 链表中的下一个节点。
	/// </summary>
	struct user *next;

};
