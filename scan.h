#pragma once
#include <time.h>
#include <math.h>

#ifdef __cplusplus
	#define __extern extern "C"
#else
	#define __extern extern
#endif

// �����ڴ沢����
#define _alloc(p,T) do { \
	p = (T*) malloc(sizeof(T)); \
	memset(p, 0x00, sizeof(T)); \
} while (false)

// ���㲢�ͷ��ڴ�
#define _free(p,T) do { \
	memset(p, 0x00, sizeof(T)); \
	free(p); \
} while (false)

// �����������
#define _pause() do { \
	printf("\n�밴���������. . . "); \
	flush(); \
	getchar(); \
	flush(); \
} while (false)

#define cent(d) ((int)floor((d)*100+0.5))
#define dollar(c) ((c)/100.0)

#ifdef WINVER
	// ���stdin�Ķ�������
	#define flush() rewind(stdin)
	// ����Ļ
	#define clear() system("cls")
	// ���<Windows.h, Kernel32.lib>
	__extern void __stdcall Sleep(unsigned long dwMilliseconds);
	// ��ͣa����
	#define sleep(a) Sleep(a)
	// localtime�̰߳�ȫ
	#define LocalTime(a,b) localtime_s(a,b)
#else
	#include <unistd.h>
	#include <stdio_ext.h>
	// ���stdin�Ķ�������
	#define flush() __fpurge(stdin)
	// ����Ļ
	#define clear() system("clear")
	// ��ͣa����
	#define sleep(a) usleep((a)*1000)
	// localtime�̰߳�ȫ
	#define LocalTime(a,b) localtime_r(b,a)
#endif

// ������ֵ����a��b��ֵ
#define swap(a,b) (a)^=(b)^=(a)^=(b)

extern time_t pTime;
extern struct tm pDate;
extern bool bFresh;

/// <summary>��ȡһ��0001-9999������</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
/// <param name="i" type="Short">Ҫɨ��ı�����ַ</param>
/// <param name="canFF" type="Boolean">�Ƿ��������-1</param>
void ScanShort(const char* message, short *i, bool canFF);

/// <summary>��ȡһ��32λ����</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
/// <param name="i" type="Integer">Ҫɨ��ı�����ַ</param>
void ScanInt(const char* message, int *i);

/// <summary>ɨ��һ��˫���ȸ�����</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
/// <param name="i" type="Double">Ҫɨ��ı�����ַ</param>
void ScanDouble(const char* message, double *i);

/// <summary>ɨ��һ�������ո���ַ���</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
/// <param name="buffer" type="Char[]">Ҫɨ��ı�����ַ</param>
/// <param name="len" type="Integer">�ַ��������󳤶�</param>
void ScanText(const char* message, char *buffer, size_t len);

/// <summary>ɨ���������ַ���Ϊѡ��</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
/// <param name="min" type="Char">ѡ����ASCII��С���ַ�</param>
/// <param name="max" type="Char">ѡ����ASCII�����ַ�</param>
char ScanOption(const char* message, const char min, const char max);

/// <summary>ɨ���� / ��ѡ��</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
bool ScanBoolean(const char* message);

/// <summary>�򿪲����ļ������ݸ���</summary>
/// <param name="pFile" type="File">�ļ�ָ��</param>
/// <param name="pszName" type="String">�ļ���</param>
/// <param name="dwStruct" type="Integer">�ṹ���С</param>
int OpenFile(FILE* *pFile, const char* pszName, size_t dwStruct);

/// <summary>ɨ��ʱ��</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
time_t ScanTime(const char* message);

/// <summary>��ʼ����ǰ����</summary>
void SetCurrentDate();

/// <summary>����ڶ���</summary>
void push_date();

/// <summary>��������ո�</summary>
/// <param name="buf" type="String">ԭ�ַ���</param>
/// <param name="len" type="Integer">����������</param>
void trim(char *buf, size_t len);

/// <summary>���˵�</summary>
void menu_main();

/// <summary>ˢ������</summary>
/// <param name="bClear" type="Boolean">������������</param>
void flush_data();
