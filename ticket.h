#pragma once
#include "structs.h"

extern ticket *pTicketFront;
extern ticket *pTicketRear;
extern ticket *pTicketTemp;

/// <summary>���ļ�����СƱ��Ϣ</summary>
void LoadTicketFromFile();

/// <summary>��СƱ������ļ�</summary>
bool SaveTicketToFile();

/// <summary>���һ��СƱ</summary>
bool AddTicket();

/// <summary>���һ��СƱ����Ϣ</summary>
/// <param name="ticket" type="Ticket">Ҫ�����СƱ</param>
void OutputTicket(ticket* ticket);

/// <summary>����ļ��Ƿ�򿪳ɹ�</summary>
/// <param name="pFile" type="File">Ҫ�����ļ�ָ��</param>
/// <param name="pszName" type="String">�ļ���</param>
void OutputAllTickets();

/// <summary>��СƱ�������</summary>
/// <param name="tid" type="Short">Ҫ�����ļ�ָ��</param>
/// <returns>NULLΪδ�ҵ�СƱ</returns>
ticket *FindTicket(short tid);

/// <summary>�޸�СƱ����</summary>
/// <param name="tid" type="Short">Ҫ���ĵ�СƱ���</param>
bool ModifyTicket(short tid);

/// <summary>ɾ��СƱ</summary>
/// <param name="tid" type="Short">Ҫɾ����СƱ���</param>
bool DeleteTicket(short tid);

ticket *GetCardBytid(short tid);
void printticket();