#pragma once
#include "structs.h"

bool LoadStockFromFile(struct stock warehouse[5]);
bool SaveStockToFile(struct stock warehouse[5]);
void OutputStock();
bool AddStock(int count);
