#pragma once
#include <time.h>
#include <math.h>
#include <sys/stat.h>

#ifdef __cplusplus
	#define __extern extern "C"
#else
	#define __extern extern
#endif

// 清空stdin的多余内容
#define flush() rewind(stdin)

// 文件p是否存在
#define file_exists(p) (_access(p, 0) != EOF)

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
#define pause() do { \
	printf("\n请按任意键继续. . . "); \
	flush(); \
	getchar(); \
	flush(); \
} while (false)

#define cent(d) ((int)floor((d)*100+0.5))
#define dollar(c) ((c)/100.0)

#ifdef WINVER
	// 清屏幕
	#define clear() system("cls")
	// 详见<Windows.h, Kernel32.lib>
	__extern void __stdcall Sleep(unsigned long dwMilliseconds);
	// 暂停a毫秒
	#define sleep(a) Sleep(a)
#else
	#include <unistd.h>
	// 清屏幕
	#define clear() system("clear")
	// 暂停a毫秒
	#define sleep(a) usleep((a)*1000)
#endif

// 交换数值类型a和b的值
#define swap(a,b) (a)^=(b)^=(a)^=(b)

extern time_t pTime;
extern struct tm *pCurrentDate;

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

/// <summary>检查文件是否打开成功</summary>
/// <param name="pFile" type="File">要检查的文件指针</param>
/// <param name="pszName" type="String">文件名</param>
void CheckFile(FILE* pFile, const char* pszName);

/// <summary>文件被破坏时退出</summary>
/// <param name="pFile" type="File">文件指针</param>
/// <param name="pszName" type="String">文件名</param>
void DataNotFulfilled(FILE* pFile, const char* pszName);

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
void flush_data();
