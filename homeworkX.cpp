#include "stdafx.h"

#include <stdio.h>
#ifndef DebugBreak
#define DebugBreak()
#endif

struct item {
	int value;
	struct item *next;
} p = { 0 , NULL }, *first = &p, *ptr = &p;

int main_hw11_2()
{
	int integer;
	while (1)
	{
		scanf("%d", &integer);
		if (integer == 0) break;
		ptr->next = (struct item*) malloc(sizeof(struct item));
		ptr = ptr->next;
		ptr->value = integer;
		ptr->next = NULL;
	}
	ptr = first;
	scanf("%d", &integer);
	while (ptr->next != NULL)
	{
		while (ptr->next->value == integer)
			ptr->next = ptr->next->next;
		ptr = ptr->next;
	}
	ptr = first;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		printf("%d", ptr->value);
	}
	printf("\n");
	DebugBreak();
	return 0;
}

int main_hw11_1()
{
	int integer;
	while (1)
	{
		scanf("%d", &integer);
		if (integer == 0) break;
		ptr->next = (struct item*) malloc(sizeof(struct item));
		ptr = ptr->next;
		ptr->value = integer;
		ptr->next = NULL;
	}
	ptr = first;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		printf("%d", ptr->value);
	}
	printf("\n");
	DebugBreak();
	return 0;
}

int main_hw10_1()
{
	unsigned int n, square, exp, temp;
	scanf("%u", &n);
	for (int i = 1; i <= n; i++)
	{
		exp = 1, temp = i;
		while (temp)
			temp /= 10, exp *= 10;
		square = i * i;
		if (square % exp == i)
			printf("%d\n", i);
	}
	DebugBreak();
	return 0;
}