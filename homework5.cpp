#include "stdafx.h"

#include <stdio.h>

void moveArray(int d[10], int move)
{
	for (; move > 0; move--) {
		int temp = d[9];
		for (int i = 9; i > 0; i--)
			d[i] = d[i - 1];
		d[0] = temp;
	}
}

int main_hw5_4() {
	int d[10], move;
	for (int i = 0; i < 10; i++)
		scanf("%d", d + i);
	scanf("%d", &move);
	moveArray(d, move);
	for (int i = 0; i < 10; i++)
		printf("%d", d[i]);
	printf("\n");
	DebugBreak();
	return 0;
}

int main_hw5_3() {
	int d[10];
	for (int i = 0; i < 10; i++)
		scanf("%d", d + i);
	for (int j = 8; j >= 0; j--)
		if (d[j] == 0) {
			for (int k = j; k < 9; k++) {
				int t = d[k];
				d[k] = d[k + 1];
				d[k + 1] = t;
			}
		}
	for (int i = 0; i < 10; i++)
		printf("%d", d[i]);
	printf("\n");
	DebugBreak();
	return 0;
}

int main_hw5_2() {
	int p, r, g, s, b, q;
	scanf("%d", &p);
	if (p < 1000 || p > 9999)
		r = 0;
	else {
		q = p;
		g = q % 10;
		q /= 10;
		s = q % 10;
		q /= 10;
		b = q % 10;
		q /= 10;
		r = g * 1000 + s * 100 + b * 10 + q;
	}
	printf("%d\n", r);
	DebugBreak();
	return 0;
}

int main_hw5_1() {
	int m, n, result;
	scanf("%d %d", &m, &n);
	if (m > 0 && n >= 0) {
		if (m < n)
			result = 0;
		if (m == n)
			result = 1;
		if (m > n) {
			result = 1;
			for (int t = m; t > m - n; t--)
				result *= t;
			for (int k = 1; k <= n; k++)
				result /= k;
		}
	} else {
		result = -1;
	}
	printf("%d\n", result);
	DebugBreak();
	return 0;
}