#include <assert.h>
#include <math.h>
#include <stdio.h>

unsigned char is_prime(unsigned int n) {
	unsigned int i;
	if (n < 2)
		return 0;
	for (i = 2; i * i <= n; ++i) {
		if (n % i == 0)
			return 0;
	}
	return 1;
}

unsigned int get_lower_bound(unsigned int n) {
	double log_n;
	assert(n > 0);
	log_n = log((double)n);
	return n * (unsigned int)round(log_n + log(log_n) - 1.0);
}

unsigned int nth_prime(unsigned int n) {
	unsigned int i, start = get_lower_bound(n);
	for (i = start + n - 1; i > start; --i) {
		if (is_prime(i))
			return i;
	}
	return 0;
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1 || n < 1) {
		fprintf(stderr, "Invalid input. Input one positive integer.\n");
		return 1;
	}
	printf("%u\n", nth_prime(n));
	return 0;
}
