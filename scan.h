#pragma once

/// <summary>��ȡһ��0001-9999������</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
/// <param name="i" type="Short">Ҫɨ��ı�����ַ</param>
void ScanShort(const char* message, short *i);

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
/// <param name="c" type="Char">Ҫɨ��ı�����ַ</param>
void ScanOption(const char* message, const char min, const char max, char *c);

/// <summary>ɨ���� / ��ѡ��</summary>
/// <param name="message" type="String">��ʾ����Ϣ</param>
bool ScanBoolean(const char* message);
