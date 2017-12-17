#pragma once
#include "structs.h"

extern ticket *pTicketFront;
extern ticket *pTicketRear;
extern ticket *pTicketTemp;

/// <summary>从文件加载小票信息</summary>
void LoadTicketFromFile();

/// <summary>将小票保存进文件</summary>
bool SaveTicketToFile();

/// <summary>添加一张小票</summary>
bool AddTicket();

/// <summary>输出一张小票的信息</summary>
/// <param name="ticket" type="Ticket">要输出的小票</param>
void OutputTicket(ticket* ticket);

/// <summary>检查文件是否打开成功</summary>
/// <param name="pFile" type="File">要检查的文件指针</param>
/// <param name="pszName" type="String">文件名</param>
void OutputAllTickets();

/// <summary>按小票号码查找</summary>
/// <param name="tid" type="Short">要检查的文件指针</param>
/// <returns>NULL为未找到小票</returns>
ticket *FindTicket(short tid);

/// <summary>修改小票内容</summary>
/// <param name="tid" type="Short">要更改的小票编号</param>
bool ModifyTicket(short tid);

/// <summary>删除小票</summary>
/// <param name="tid" type="Short">要删除的小票编号</param>
bool DeleteTicket(short tid);

ticket *GetCardBytid(short tid);
void printticket();