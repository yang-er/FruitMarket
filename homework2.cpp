#include "stdafx.h"
#include <stdio.h>

int main_lab1_3() {
	int a, b, c, d, e;
	scanf("%d %d", &a, &b);
	c = a % 10, a /= 10;
	d = b % 10, b /= 10;
	e = d * 1000 + a * 100 + b * 10 + c;
	printf("%d", e);
	DebugBreak();
	return 0;
}

int main_lab1_2() {
	int a, b;
	scanf("%d %d", &a, &b);
	a = a + b;
	b = a - b;
	a = a - b;
	printf("%d %d\n", a, b);
	DebugBreak();
	return 0;
}

int main_hw2_4() {
	int c;
	scanf("%d", &c);
	float f = 32.0F + 1.8F * c;
	printf("%.3f", f);
	DebugBreak();
	return 0;
}

int main_hw2_3() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d %d %d %d %d", a + b, a - b, a * b, a / b, a % b);
	DebugBreak();
	return 0;
}

int main_hw2_2() {
	float a, b, c;
	scanf("%f %f %f", &a, &b, &c);
	float d = (a + b + c) / 3.0F;
	printf("%.3f", d);
	DebugBreak();
	return 0;
}

int main_hw2_1()
{
	int chInput = getchar();
	putchar(chInput - 1);
	putchar(chInput);
	putchar(chInput + 1);
	DebugBreak();
	return 0;
}
