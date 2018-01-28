#include "stdafx.h"

#include <stdio.h>
#ifndef DebugBreak()
#define DebugBreak() 
#endif

int main_lab3_4() {
	int m, n, **arr, *buffer, temp, *temp_ptr;
	scanf("%d %d", &m, &n);
	buffer = (int*) malloc(sizeof(int) * m * n);
	for (int i = 0; i < m * n; i++)
		scanf("%d", buffer + i);
	arr = (int**) malloc(sizeof(int*) * m);
	for (int i = 0; i < m; i++)
		arr[i] = buffer + i * n;
	for (int i = 0; i < m; i++)
		for (int j = n - 1; j >= 0; j--)
			for (int k = j; k < n - 1; k++)
				if (arr[i][k] > arr[i][k + 1])
					temp = arr[i][k + 1], arr[i][k + 1] = arr[i][k], arr[i][k] = temp;
	for (int i = 0; i < m - 1; i++)
		if (arr[i][0] > arr[i + 1][0])
			temp_ptr = arr[i], arr[i] = arr[i + 1], arr[i + 1] = temp_ptr;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	DebugBreak();
	return 0;
}

int main_hw6_4() {
	int a[5], b[5];
	scanf("%d %d %d %d %d", a, a + 1, a + 2, a + 3, a + 4);
	for (int i = 0; i < 5; i++) {
		int count = 0;
		for (int j = 0; j < 5; j++)
			if (a[i] > a[j]) count++;
		b[i] = count;
	}
	printf("%d%d%d%d%d\n", a[0], a[1], a[2], a[3], a[4]);
	printf("%d%d%d%d%d\n", b[0], b[1], b[2], b[3], b[4]);
	return 0;
}

#include <string.h>

int main_hw6_5() {
	char string[21];
	//scanf("%s", string);
	gets(string);
	int length = strlen(string);
	for (int i = 0; i < length / 2; i++) {
		char t = string[i];
		string[i] = string[length - 1 - i];
		string[length - 1 - i] = t;
	}
	printf("%s\n", string);
	return 0;
}

int main_hw6_1() {
	int a[3][3], *p = a[0], result = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			scanf("%d", &a[i][j]);
	for (int k = 0; k < 8; k++)
		for (int h = k + 1; h < 9; h++)
			if (*(p + k) == *(p + h))
				result |= 1;
	if (result == 1)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}

int main_hw6_3() {
	int a[3][3], result = 1;
	for (int i = 0; i < 3; i++)
		scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
	if (a[0][1] != a[1][0]) result &= 0;
	if (a[0][2] != a[2][0]) result &= 0;
	if (a[1][2] != a[2][1]) result &= 0;
	if (result == 1)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}

#define swap(a, b) a=a+b, b=a-b, a=a-b

int main_hw6_2() {
	int a[3][3];
	for (int i = 0; i < 3; i++)
		scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
	swap(a[0][1], a[1][0]);
	swap(a[0][2], a[2][0]);
	swap(a[1][2], a[2][1]);
	for (int i = 0; i < 3; i++)
		printf("%d%d%d", a[i][0], a[i][1], a[i][2]);
	printf("\n");
	return 0;
}

int main_hw6_1_old() {
	int a[3][3], result = 0;
	scanf("%d%d%d%d%d%d%d%d%d",
		&a[0][0], &a[0][1], &a[0][2],
		&a[1][0], &a[1][1], &a[1][2],
		&a[2][0], &a[2][1], &a[2][2]
	);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				for (int h = 0; h < 3; h++)
					if (a[i][j] == a[k][h] && !(i == k && j == h))
						result |= 1;
	if (result == 1)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}
