#include <inttypes.h>
#include <stdio.h>

#define UINT32_FACT_MAX 12

void fs(uint32_t n) {
	const size_t s = UINT32_FACT_MAX;
	size_t i;
	uint32_t factorials[s];
	for (i = 1; i < s + 1; i++) {
		if (i <= 1)
			factorials[i] = 1;
		else
			factorials[i] = i * factorials[i - 1];
		if (factorials[i] > n)
			break;
	}
	for (size_t j = (i > 1) ? i - 1 : 1; j > 0; j--) {
		uint32_t m = n / factorials[j];
		if (m != 0)
			n %= m * factorials[j];
		printf("%" PRIu32 ".", m);
	}
	fputc('\n', stdout);
}

int main(void) {
	uint32_t n;
	if (scanf("%" PRIu32, &n) != 1)
		return 1;
	fs(n);
	return 0;
}
