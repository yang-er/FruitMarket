#pragma once
#include "structs.h"

extern struct stock warehouse[5];

/// <summary>���ļ��м��ؿ����Ϣ</summary>
bool LoadStockFromFile();

/// <summary>��ˮ�������Ϣ���浽�ļ�</summary>
bool SaveStockToFile();

/// <summary>�������ˮ���Ŀ��</summary>
void OutputStock();

/// <summary>����ĳһˮ���Ŀ��</summary>
bool AddStock();
