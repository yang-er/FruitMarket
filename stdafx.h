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

// 文件p是否存在
#define file_exists(p) (_access(p, 0) != EOF)

#ifdef WINVER
#include <Windows.h>
// 清屏幕
#define _clear() system("cls")
// 暂停a毫秒
#define _sleep(a) Sleep(a)
#else
#include <unistd.h>
// 清屏幕
#define _clear() system("clear")
// 暂停a毫秒
#define _sleep(a) usleep(a*1000)
#endif

/// <summary>检查文件是否打开成功</summary>
/// <param name="pFile" type="File">要检查的文件指针</param>
/// <param name="pszName" type="String">文件名</param>
void CheckFile(FILE* pFile, const char* pszName);

/// <summary>文件被破坏时退出</summary>
/// <param name="pFile" type="File">文件指针</param>
/// <param name="pszName" type="String">文件名</param>
void DataNotFulfilled(FILE* pFile, const char* pszName);
