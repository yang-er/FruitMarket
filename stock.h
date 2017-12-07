#pragma once
#include "structs.h"

bool LoadStockFromFile(struct stock warehouse[5]);
bool SaveStockToFile(struct stock warehouse[5]);
void OutputStock(struct stock warehouse[5]);
bool AddStock(struct stock fruit, int count);
