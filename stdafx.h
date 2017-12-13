#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
#define DEBUG
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>

#define gets gets_s
#define file_exists(p) (_access(p, 0) != EOF)
#ifdef WINVER
#define ClearScreen() system("cls")
#else
#define ClearScreen() system("clear")
#endif

/// <summary>����ļ��Ƿ�򿪳ɹ�</summary>
/// <param name="pFile" type="File">Ҫ�����ļ�ָ��</param>
/// <param name="pszName" type="String">�ļ���</param>
void CheckFile(FILE* pFile, const char* pszName);

/// <summary>�ļ����ƻ�ʱ�˳�</summary>
/// <param name="pFile" type="File">�ļ�ָ��</param>
/// <param name="pszName" type="String">�ļ���</param>
void DataNotFulfilled(FILE* pFile, const char* pszName);
