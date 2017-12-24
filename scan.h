#pragma once
#include <time.h>
#include <math.h>

#ifdef __cplusplus
	#define __extern extern "C"
#else
	#define __extern extern
#endif

// 申请内存并清零
#define _alloc(p,T) do { \
	p = (T*) malloc(sizeof(T)); \
	memset(p, 0x00, sizeof(T)); \
} while (false)

// 清零并释放内存
#define _free(p,T) do { \
	memset(p, 0x00, sizeof(T)); \
	free(p); \
} while (false)

// 按任意键继续
#define _pause() do { \
	printf("\n请按任意键继续. . . "); \
	flush(); \
	getchar(); \
	flush(); \
} while (false)

#define cent(d) ((int)floor((d)*100+0.5))
#define dollar(c) ((c)/100.0)

#ifdef WINVER
	// 清空stdin的多余内容
	#define flush() rewind(stdin)
	// 清屏幕
	#define clear() system("cls")
	// 详见<Windows.h, Kernel32.lib>
	__extern void __stdcall Sleep(unsigned long dwMilliseconds);
	// 暂停a毫秒
	#define sleep(a) Sleep(a)
	// localtime线程安全
	#define LocalTime(a,b) localtime_s(a,b)
#else
	#include <unistd.h>
	#include <stdio_ext.h>
	// 清空stdin的多余内容
	#define flush() __fpurge(stdin)
	// 清屏幕
	#define clear() system("clear")
	// 暂停a毫秒
	#define sleep(a) usleep((a)*1000)
	// localtime线程安全
	#define LocalTime(a,b) localtime_r(b,a)
#endif

// 交换数值类型a和b的值
#define swap(a,b) (a)^=(b)^=(a)^=(b)

extern time_t pTime;
extern struct tm pDate;
extern bool bFresh;

/// <summary>读取一个0001-9999的数字</summary>
/// <param name="message" type="String">显示的消息</param>
/// <param name="i" type="Short">要扫描的变量地址</param>
/// <param name="canFF" type="Boolean">是否可以输入-1</param>
void ScanShort(const char* message, short *i, bool canFF);

/// <summary>读取一个32位整数</summary>
/// <param name="message" type="String">显示的消息</param>
/// <param name="i" type="Integer">要扫描的变量地址</param>
void ScanInt(const char* message, int *i);

/// <summary>扫描一个双精度浮点数</summary>
/// <param name="message" type="String">显示的消息</param>
/// <param name="i" type="Double">要扫描的变量地址</param>
void ScanDouble(const char* message, double *i);

/// <summary>扫描一个不带空格的字符串</summary>
/// <param name="message" type="String">显示的消息</param>
/// <param name="buffer" type="Char[]">要扫描的变量地址</param>
/// <param name="len" type="Integer">字符数组的最大长度</param>
void ScanText(const char* message, char *buffer, size_t len);

/// <summary>扫描连续的字符作为选项</summary>
/// <param name="message" type="String">显示的消息</param>
/// <param name="min" type="Char">选项中ASCII最小的字符</param>
/// <param name="max" type="Char">选项中ASCII最大的字符</param>
char ScanOption(const char* message, const char min, const char max);

/// <summary>扫描是 / 否选项</summary>
/// <param name="message" type="String">显示的消息</param>
bool ScanBoolean(const char* message);

/// <summary>打开并数文件中数据个数</summary>
/// <param name="pFile" type="File">文件指针</param>
/// <param name="pszName" type="String">文件名</param>
/// <param name="dwStruct" type="Integer">结构体大小</param>
int OpenFile(FILE* *pFile, const char* pszName, size_t dwStruct);

/// <summary>扫描时间</summary>
/// <param name="message" type="String">显示的消息</param>
time_t ScanTime(const char* message);

/// <summary>初始化当前日期</summary>
void SetCurrentDate();

/// <summary>进入第二天</summary>
void push_date();

/// <summary>左右清除空格</summary>
/// <param name="buf" type="String">原字符串</param>
/// <param name="len" type="Integer">缓冲区长度</param>
void trim(char *buf, size_t len);

/// <summary>主菜单</summary>
void menu_main();

/// <summary>刷新数据</summary>
/// <param name="bClear" type="Boolean">清除或更新数据</param>
void flush_data();
