#include "stdafx.h"

#include <stdio.h>
#include <math.h>

#define distance(a,b) sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))

struct point {
	double x;
	double y;
} points[10];

int main_hw8_4() {
	int count;
	double length = 0;
	scanf("%d", &count);
	for (int i = 0; i < count; i++) {
		scanf("%lf %lf", &(points[i].x), &(points[i].y));
		if (i > 0)
			length += distance(points[i], points[i - 1]);
		if (i == count - 1)
			length += distance(points[i], points[0]);
	}
	printf("%.2lf\n", length);
	return 0;
}

#include <string.h>

void swap_hw8_3(char *s1, char *s2) {
	char temp[100];
	strcpy(temp, s1);
	strcpy(s1, s2);
	strcpy(s2, temp);
}

int main_hw8_3() {
	char str1[100], str2[100];
	scanf("%s %s", str1, str2);
	swap_hw8_3(str1, str2);
	printf("%s\n%s\n", str1, str2);
	return 0;
}

int main_hw8_2() {
	int big = 0, small = 0, blank = 0, number = 0;
	for (char read = getchar(); read != '@'; read = getchar()) {
		if (read == ' ') blank++;
		else if (read >= 'a' && read <= 'z') small++;
		else if (read >= 'A' && read <= 'Z') big++;
		else if (read >= '0' && read <= '9') number++;
	}
	printf("%d %d %d %d\n", big, small, blank, number);
	return 0;
}

int main_hw8_1() {
	char str[100];
	int len = 0;
	scanf("%s", str);
	for (; str[len] != '\0'; len++);
	printf("%d\n", len);
	return 0;
}