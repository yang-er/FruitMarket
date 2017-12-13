#pragma once

/// <summary>读取一个0001-9999的数字</summary>
/// <param name="message" type="String">显示的消息</param>
/// <param name="i" type="Short">要扫描的变量地址</param>
void ScanShort(const char* message, short *i);

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
/// <param name="c" type="Char">要扫描的变量地址</param>
void ScanOption(const char* message, const char min, const char max, char *c);

/// <summary>扫描是 / 否选项</summary>
/// <param name="message" type="String">显示的消息</param>
bool ScanBoolean(const char* message);
