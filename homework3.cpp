#include "stdafx.h"
#include <stdio.h>

int main_lab1_4() {
	char text[101];
	//scanf("%s", text);
	gets(text);
	int summary = strlen(text);
	for (int i = 0; i < summary; i++)
		text[i] = toupper(text[i]);
	printf("%s\n", text);
	return 0;
}

int main_hw3_4() {
	int sup;
	scanf("%d", &sup);
	for (int i = 1; i < sup; i++) {
		if (i % 11 == 0)
			printf("%d", i);
	}
	printf("\n");
	return 0;
}

int main_hw3_3() {
	int flag = 0, check_num;
	char *result[] = { "never can be", "7", "5", "5,7", "3", "3,7", "3,5", "3,5,7" };
	scanf("%d", &check_num);
	if (check_num % 3 == 0)
		flag |= 4;
	if (check_num % 5 == 0)
		flag |= 2;
	if (check_num % 7 == 0)
		flag |= 1;
	printf("%s\n", result[flag]);
	return 0;
}

int main_hw3_2() {
	int test_num;
	scanf("%d", &test_num);
	short k = test_num;
	short i = k / 100;
	k %= 100;
	short j = k / 10;
	k %= 10;
	int cube = i*i*i + k*k*k + j*j*j;
	if (cube == test_num)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}

int main_hw3_1_new() {
	float a, b, c, t;
	scanf("%f %f %f", &a, &b, &c);
	if (a > c) { t = a; a = c; c = t; }
	if (b > c) { t = b; b = c; c = t; }
	if (a > b) { t = b; b = a; a = t; }
	printf("%.1f %.1f %.1f\n", a, b, c);
	return 0;
}

int main_hw3_1_old() {
	float a[3];
	scanf("%f %f %f", a, a + 1, a + 2);
	for (int i = 0; i < 3; i++) {
		for (int j = i; j > 0; j--) {
			if (a[j - 1] > a[j]) {
				float c = a[j];
				a[j] = a[j - 1];
				a[j - 1] = c;
			}
		}
	}
	printf("%.1f %.1f %.1f\n", a[0], a[1], a[2]);
	return 0;
}

/*

#include <stdio.h>

int main() {
	int i, j;
	double c;
	double a[10];
	scanf("%lf %lf %lf", a+1, a+2, a+3);
	for (i = 1; i <= 3; i++) {
		for (j = i; j > 0; j--) {
			if (a[j - 1] > a[j]) {
				double c = a[j];
				a[j] = a[j - 1];
				a[j - 1] = c;
			}
		}
	}
	printf("%.1lf %.1lf %.1lf", a[1], a[2], a[3]);
	printf("\n");
	return 0;
}


*/
