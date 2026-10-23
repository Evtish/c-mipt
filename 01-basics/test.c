#include <inttypes.h>
#include <math.h>
#include <stdio.h>

int main(void) {
	int32_t x;
	if (scanf("%" PRIi32, &x) != 1 || x < 0) {
		fprintf(stderr, "Input one non-negative number\n");
		return 1;
	}
	const double sqrt5 = sqrt(5.0);
	const size_t n =
		(size_t)(log(x * sqrt5 + 0.5) / log((1.0 + sqrt5) / 2.0)) - 1;
	printf("%zu\n", n);
	return 0;
}
