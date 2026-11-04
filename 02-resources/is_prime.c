#include <stdio.h>

int is_prime(unsigned int n) {
	if (n < 2)
		return 0;
	for (unsigned int i = 2; i * i <= n; ++i) {
		if (n % i == 0)
			return 0;
	}
	return 1;
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1)
		return 1;
	printf("%d\n", is_prime(n));
	return 0;
}
