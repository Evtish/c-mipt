#include <stdio.h>

unsigned long long fib(unsigned int n) {
	unsigned long long a = 0ULL, b = 1ULL, tmp;
	while (n) {
		tmp = a;
		a += b;
		b = tmp;
		n--;
	}
	return a;
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1)
		return 1;
	printf("%llu\n", fib(n));
	return 0;
}
