#include <stdio.h>

unsigned int factorial(unsigned int n) {
	unsigned int f = 1;
	while (n > 1) {
		f *= n;
		n--;
	}
	return f;
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1)
		return 1;
	printf("%u\n", factorial(n));
	return 0;
}
