#include <math.h>
#include <stdio.h>

unsigned long long fib(unsigned int n) {
	long double sqrt5 = sqrtl(5.0L);
	long double phi = (1.0L + sqrt5) / 2.0L;
	long double phi2 = (1.0L - sqrt5) / 2.0L;
	return (unsigned long long)((powl(phi, n) - powl(phi2, n)) / sqrt5);
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1)
		return 1;
	printf("%llu\n", fib(n));
	return 0;
}
