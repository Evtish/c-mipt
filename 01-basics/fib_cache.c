#include <stdio.h>
#include <string.h>

#define OFFSET 3

unsigned long long fib(unsigned int n, unsigned long long *cache) {
	const size_t idx = n - OFFSET;
	if (n == 0)
		return 0ULL;
	if (n <= 2)
		return 1ULL;
	if (cache[idx])
		return cache[idx];
	cache[idx] = fib(n - 1, cache) + fib(n - 2, cache);
	return cache[idx];
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1)
		return 1;
	const size_t len = (n >= OFFSET) ? n + 1 - OFFSET : 1;
	unsigned long long cache[len];
	memset(cache, 0, len * sizeof(cache[0]));
	printf("%llu\n", fib(n, cache));
	return 0;
}
