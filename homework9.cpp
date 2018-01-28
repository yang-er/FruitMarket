#include "stdafx.h"

#include <stdio.h>
#ifndef DebugBreak()
#define DebugBreak() 
#endif

int max4Array(int *ptr, int left) {
	if (left == 1) return *ptr;
	else {
		int nextResult = max4Array(ptr + 1, left - 1);
		return nextResult > *ptr ? nextResult : *ptr;
	}
}

int main_hw9_4() {
	int a[10], max;
	for (int i = 0; i < 10; scanf("%d", a + i++));
	max = max4Array(a, 10);
	printf("%d\n", max);
	DebugBreak();
	return 0;
}

unsigned int Ack(unsigned int m, unsigned int n) {
	if (m == 0) return n + 1;
	else if (n == 0) return Ack(m - 1, 1);
	else return Ack(m - 1, Ack(m, n - 1));
}

int main_hw9_3() {
	unsigned int m, n, result;
	scanf("%u %u", &m, &n);
	result = Ack(m, n);
	printf("%u\n", result);
	DebugBreak();
	return 0;
}

float H(unsigned int n, float x) {
	if (n > 1) return 2 * x * H(n - 1, x) - 2 * (n - 1) * H(n - 2, x);
	else if (n == 1) return 2 * x;
	else return 1;
}

int main_hw9_2() {
	unsigned int n;
	float x, result;
	scanf("%u %f", &n, &x);
	result = H(n, x);
	printf("%.2f\n", result);
	DebugBreak();
	return 0;
}

int C(int m, int n) {
	if (n < 0) return 0;
	else if (n == 0) return 1;
	else if (n == 1) return m;
	else if (m < 2 * n) return C(m, m - n);
	else return C(m - 1, n - 1) + C(m - 1, n);
}

int main_hw9_1() {
	int m, n, Cmn;
	scanf("%d %d", &m, &n);
	Cmn = C(m, n);
	printf("%d\n", Cmn);
	DebugBreak();
	return 0;
}