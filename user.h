#pragma once
#include "structs.h"

extern user *pUserFront;
extern user *pUserRear;
extern user *pUserTemp;

/// <summary>���ļ������û���Ϣ</summary>
void LoadUserFromFile();

/// <summary>���û���Ϣ���浽�ļ�</summary>
bool SaveUserToFile();

/// <summary>�½���Ա��</summary>
void CreateCard();

/// <summary>���ٻ�Ա��</summary>
bool CrashCard();

/// <summary>�������ҿ���¼</summary>
/// <param name="uid" type="Short">�û����</param>
user *GetCardById(short uid);

/// <summary>���ڳ�ֵ</summary>
/// <param name="uid" type="Short">�û����</param>
/// <param name="credit" type="Integer">Ǯ����Ŀ</param>
/// <param name="isAdd" type="Boolean">trueΪ��ֵ��falseΪ�ۿ�</param>
bool ChargeToCard(short uid, int credit, bool isAdd);

/// <summary>�г��û���Ϣ</summary>
/// <param name="current" type="User">��ǰ�Ļ�Ա</param>
bool ListVip(user *current);

/// <summary>�г����е��û�</summary>
void ListAllVips();

/// <summary>�޸��û���Ϣ</summary>
/// <param name="uid" type="Short">�û����</param>
bool ChangeVip(short uid);

/// <summary>����̨��ӡ�û���Ϣ</summary>
void PrintVip();

/// <summary>����̨��ֵ�����</summary>
/// <param name="uid" type="Short">�û���ţ�-2Ϊ���룩</param>
void ChargeInConsole(short uid);

/// <summary>�����û�ģ��</summary>
void menu_user();
