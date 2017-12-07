#pragma once
#include <stdio.h>

void ScanShort(const char* message, short *i);
void ScanInt(const char* message, int *i);
void ScanText(const char* message, char *buffer, int len);
void ScanOption(const char* message, const char min, const char max, char *c);
bool ScanBoolean(const char* message);
