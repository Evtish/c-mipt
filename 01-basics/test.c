#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

static int get_n(int n) {
	double log_n;
	assert(n > 0);
	if (n == 1)
		return 3 / CHAR_BIT + 1;
	log_n = log((double)n);
	return n * (int)round(log_n + log(log_n)) / CHAR_BIT + 1;
}

int main(void) {
	int n;
	if (scanf("%d", &n) != 1 || n <= 0) {
		fprintf(stderr, "Invalid input. Input one positive integer\n");
		return 1;
	}
	printf("%d\n", get_n(n));
	return 0;
}
