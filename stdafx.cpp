// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// FruitMarket.pch ����ΪԤ�����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������

void CheckFile(FILE* pFile, const char* pszName)
{
	if (pFile == NULL)
	{
		fprintf(stderr, "�ļ�%s��ʧ�ܣ��˳��С���", pszName);
		exit(4);
	}
}

void DataNotFulfilled(FILE* pFile, const char* pszName)
{
	fprintf(stderr, "%s�ļ����ݱ��ƻ����޷�У��ͨ����", pszName);
	exit(4);
}
