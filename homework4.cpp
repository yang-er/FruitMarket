#include "stdafx.h"

#include <stdio.h>

#include <math.h>

int main_lab2_4() {
	double x, a = 1.0, b = 0.0;
	scanf("%lf", &x);
	b = 0.5 * (a + x / a);
	while (fabs(a - b) > 1e-10) {
		a = b;
		b = 0.5 * (a + (x / a));
	}
	printf("%.9lf\n", b);
	return 0;
}

int main_lab2_3() {
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10 - i; j++)
			printf(" ");
		for (int j = 1; j < i; j++)
			printf("%d", j);
		printf("%d", i % 10);
		for (int j = i - 1; j > 0; j--)
			printf("%d", j);
		printf("\n");
	}
	return 0;
}

int main_lab2_2() {
	for (int i = 1001; i <= 9999; i++) {
		if (i % 10 == i / 1000 && (i / 10) % 10 == (i / 100) % 10)
			printf("%d\n", i);
	}
	return 0;
}

int main_lab2_1() {
	int n, sum = 0, cur = 0;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		cur = i * i;
		if (cur >= n) break;
		sum += cur;
	}
	printf("%d\n", sum);
	return 0;
}

int main_hw4_5() {
	// Calculating e^x in Taylor's expansion with Horner scheme
	float x;
	scanf("%f", &x);
	float value = 1.0F;
	for (int i = 100; i > 0; i--) {
		value = 1 + x / i * value;
	}
	printf("%.2f\n", value);
	return 0;
}

int main_hw4_4() {
	float x;
	int n;
	scanf("%f %d", &x, &n);
	float p[100];
	p[0] = 1.0F;
	p[1] = x;
	for (int i = 2; i <= n; i++) {
		p[i] = ((float)(2 * i - 1) / (float)i * x * p[i - 1]) - ((float)(i - 1) / (float)i * p[i - 2]);
	}
	printf("%.2f\n", p[n]);
	return 0;
}

int main_hw4_3() {
	int begin = 7;
	for (;; begin += 14) {
		if (begin % 3 == 2 && begin % 5 == 4)
			break;
	}
	printf("%d\n", begin);
	return 0;
}

int main_hw4_2() {
	int s = 1, b = 0, month;
	scanf("%d", &month);
	for (int cur = 0; cur < month; cur++) {
		int c = b;
		b += s;
		s = c;
	}
	printf("%d\n", s + b);
	return 0;
}

int main_hw4_1() {
	for (int test_num = 100; test_num < 1000; test_num++) {
		short k = test_num;
		short i = k / 100;
		k %= 100;
		short j = k / 10;
		k %= 10;
		int cube = i*i*i + k*k*k + j*j*j;
		if (cube == test_num)
			printf("%d\n", test_num);
	}
	return 0;
}