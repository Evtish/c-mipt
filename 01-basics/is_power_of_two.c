#include <stdbool.h>
#include <stdio.h>

bool is_power_of_two(unsigned long long n) {
#ifdef DUMB
	if (n <= 0)
		return false;
	while (n != 1llu) {
		if (n & 1llu)
			return false;
		n >>= 1;
	}
	return true;
#else
	return (n > 0llu) && ((n & (n - 1llu)) == 0llu);
#endif
}

int main(void) {
	unsigned long long n;
	if (scanf("%llu", &n) != 1) {
		fprintf(stderr, "Invalid input. Input one non-negative number.\n");
		return 1;
	}
	printf("%d\n", is_power_of_two(n));
	return 0;
}
