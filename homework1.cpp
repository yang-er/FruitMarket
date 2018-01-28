#include "stdafx.h"
#include <stdio.h>

extern void hello();

int main_lab1_1() {
	hello();
	return 0;
}

int main_hw1_2() {
	int head = 25, foot = 72, rabbit, chicken;
	// Set rabbit as rabit, so the chicken = head - rabbit
	// We have this two linear equation:
	// rabbit * 4 + chicken * 2 = foot
	// 4 * rabbit + 2 * ( head - rabbit ) = foot
	rabbit = (foot - 2 * head) / (4 - 2);
	chicken = head - rabbit;
	printf("%d %d", chicken, rabbit);
	return 0;
}

int main_hw1_1() {
	char hello_msg[12] = "Hello World";
	printf(hello_msg);
	return 0;
}
