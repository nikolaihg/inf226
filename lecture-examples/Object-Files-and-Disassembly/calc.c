#include <stdio.h>

int cal(int x, int f, double a, unsigned char m) {
	puts("Hello, world!\n");
	int y = x * f;

	double b = a * f;

	unsigned short n = m * (unsigned short)f;

	printf("%d %f %d\n", y, b, n);

	return y;
}
