#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void read_input(int *a, int *b) {
	printf("введите a и b\n");
	if (scanf("%d%d", a, b) != 2) {
		fprintf(stderr, "принимаются только целые числа\n");
		abort();
	}
}

void sort_input(int *a, int *b) {
	if (*b > *a) {
		int buf = *a;
		*a = *b;
		*b = buf;
	}
	if (*b == 0) {
		fprintf(stderr, "на ноль делить нельзя\n");
		abort();
	}
}

// a = b * p + q
// gcd(a, b) = gcd(b, q)
int gcd(int a, int b) {
	int q = a % b;
	if (q == 0)
		return abs(b);
	return gcd(b, q);
}

int main(void) {
	int a, b;
	read_input(&a, &b);
	sort_input(&a, &b);
	assert(a >= b);
	assert(b != 0);
	printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
	return 0;
}
