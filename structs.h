#pragma once
#include <time.h>

/// <summary>购物小票</summary>
typedef struct ticket {

	/// <summary>序号（编号0001-9999）</summary>
	short tid;

	/// <summary>购物时间（见&lt;time.h&gt;）</summary>
	time_t time;

	/// <summary>水果购买数量（与warehouse对应）</summary>
	int amount[5];

	/// <summary>水果购买种类（与warehouse对应）</summary>
	int fruit;

	/// <summary>水果购买金额（与warehouse对应）</summary>
	int credit[5];

	/// <summary>会员卡号（-1为现金）</summary>
	short vipCard;

	/// <summary>收入现金 / 会员卡原余额</summary>
	int given;

	/// <summary>找零现金 / 会员卡现余额 </summary>
	int left;

	/// <summary>链表的下一个节点</summary>
	struct ticket *next;

} ticket;

/// <summary>商品库存</summary>
typedef struct stock {

	/// <summary>水果名称</summary>
	char fruitName[21];

	/// <summary>单位名称（斤 / 个 / 串等）</summary>
	char tagName[21];

	/// <summary>是否单个出售</summary>
	bool isSingled;

	/// <summary>剩余库存</summary>
	int left;

	/// <summary>今日总卖出</summary>
	int sold;

	/// <summary>单价（分为单位）</summary>
	int singlePrice;

	/// <summary>
	/// 今天卖了多少钱。
	/// </summary>
	int todayUsage;

	/// <summary>一盒多少个</summary>
	int boxCount;

} stock;

/// <summary>会员卡用户</summary>
typedef struct user {

	/// <summary>持卡人签名</summary>
	char name[21];

	/// <summary>用户编号（0001-9999）</summary>
	short uid;

	/// <summary>用户余额（分为单位）</summary>
	int balance;

	/// <summary>消费总额（分为单位）</summary>
	int todayUsage;

	/// <summary>链表的下一个节点</summary>
	struct user *next;

} user;
