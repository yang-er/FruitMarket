#pragma once
#include "structs.h"

extern user *pUserFront;
extern user *pUserRear;
extern user *pUserTemp;

/// <summary>从文件加载用户信息</summary>
void LoadUserFromFile();

/// <summary>将用户信息保存到文件</summary>
bool SaveUserToFile();

/// <summary>新建会员卡</summary>
void CreateCard();

/// <summary>销毁会员卡</summary>
bool CrashCard();

/// <summary>按卡号找卡记录</summary>
/// <param name="uid" type="Short">用户编号</param>
user *GetCardById(short uid);

/// <summary>向卡内充值</summary>
/// <param name="uid" type="Short">用户编号</param>
/// <param name="credit" type="Integer">钱的数目</param>
/// <param name="isAdd" type="Boolean">true为充值，false为扣款</param>
bool ChargeToCard(short uid, int credit, bool isAdd);

/// <summary>列出用户信息</summary>
/// <param name="current" type="User">当前的会员</param>
bool ListVip(user *current);

/// <summary>列出所有的用户</summary>
void ListAllVips();

/// <summary>修改用户信息</summary>
/// <param name="uid" type="Short">用户编号</param>
bool ChangeVip(short uid);

/// <summary>控制台打印用户信息</summary>
void PrintVip();

/// <summary>控制台充值卡金额</summary>
/// <param name="uid" type="Short">用户编号（-2为输入）</param>
void ChargeInConsole(short uid);

/// <summary>进入用户模块</summary>
void menu_user();
