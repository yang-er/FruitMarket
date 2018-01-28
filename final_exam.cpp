#include "stdafx.h"
#include <stdio.h>

int main_e4()
{
	int M[100], bottom = 0, top = 0, n, temp;
	M[0] = 1;
	scanf("%d", &n);
	for (int i = 0; bottom <= 50; i++)
	{
		M[++top] = M[i] * 2 + 1;
		for (bottom = 0; M[bottom] < M[top]; bottom++);
		bottom--;
		if (bottom < 0)bottom = 0;
		for (int p = top - 1; p >= bottom; p--)
		{
			for (int q = p; q < top; q++)
			{
				if (M[q - 1] > M[q])
				{
					temp = M[q - 1];
					M[q - 1] = M[q];
					M[q] = temp;
				}
				if (M[q - 1] == M[q])
				{
					for (int k = q; k < top; k++)
						M[k] = M[k + 1];
					top--;
				}
			}
		}
		M[++top] = M[i] * 3 + 1;
		for (int p = top - 1; p >= bottom; p--)
		{
			for (int q = p; q < top; q++)
			{
				if (M[q - 1] > M[q])
				{
					temp = M[q - 1];
					M[q - 1] = M[q];
					M[q] = temp;
				}
				if (M[q - 1] == M[q])
				{
					for (int k = q; k < top; k++)
						M[k] = M[k + 1];
					top--;
				}
			}
			if (p > 1 && M[p] > M[p - 1]) break;
		}
	}
	for (int i = 0; i < n; i++)
		printf(i == n - 1 ? "%d" : "%d ", M[i]);
	return 0;
}

int main_e3()
{
	char buf[27], tmp;
	fgets(buf, 27, stdin);
	int len = 0;
	for (; len < 26 && buf[len] != '\n' && buf[len] != '\0'; len++);
	for (int i = len - 2; i > 0; i--)
		for (int j = i; j < len; j++)
			if (buf[j] < buf[j - 1])
				tmp = buf[j], buf[j] = buf[j - 1], buf[j - 1] = tmp;
	printf("%s", buf);
	return 0;
}

int f(int m, int n)
{
	if (m <= 0 || n <= 0 || m < n)
		return -1;
	else if (n == 1)
		return m;
	else if (m == n)
		return 1;
	else
		return f(m - 1, n) + f(m - 1, n - 1);
}

int main_e2()
{
	int m, n;
	scanf("%d %d", &m, &n);
	printf("%d\n", f(m, n));
	return 0;
}

int main_e1()
{
	int p, sum = 0;
	scanf("%d", &p);
	if (p > 0)
		for (int i = 1; i <= p; i++)
			if (p % i == 0)
				sum += i;
	printf("%d\n", sum);
	return 0;
}
