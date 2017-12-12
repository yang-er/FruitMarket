#pragma once
#include "stdafx.h"
#include "structs.h"

struct user *LoadUserFromFile();
bool SaveUserToFile(struct user* vip);
int CreateCard(int credit, char name[21]);
struct user *createCard(char name[21]);
bool CrashCard(int uid);
bool ChargeToCard(int uid, int credit, bool isAdd);
bool ListVip(struct user* current);
bool ListAllVips(struct user* vipHead);
