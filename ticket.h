#pragma once
#include "structs.h"

struct ticket *LoadTicketFromFile();
bool SaveTicketToFile(struct ticket *);
bool AddTicket(struct ticket* ticketEnd);
void OutputTicket(struct ticket* ticket);
void OutputAllTickets(struct ticket* ticketHead);
struct ticket *FindTicket(short tid);
bool ModifyTicket(short tid);
bool DeleteTicket(short tid);
