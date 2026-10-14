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

// a = b * p + q
// gcd(a, b) = gcd(b, q)
int gcd(int a, int b) {
	assert(b != 0);
	int q = a % b;
	while (q != 0) {
		a = b;
		b = q;
		q = a % b;
	}
	return abs(b);
}

int main(void) {
	int a, b;
	read_input(&a, &b);
	printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
	return 0;
}
