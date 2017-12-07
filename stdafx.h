#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
#define DEBUG
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>

#define gets gets_s
#define file_exists(p) (_access(p, 0) != EOF)

void CheckFile(FILE* pFile, const char* pszName);
void DataNotFulfilled(FILE* pFile, const char* pszName);
