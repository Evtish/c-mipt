#include <math.h>
#include <stdio.h>

// Assuming base > 1 and base < 11 and n > 0
void from_dec(char *n_conv, size_t s, unsigned int n, unsigned int base) {
	n_conv[s - 1] = '\0';
	for (size_t i = s - 1; i > 0; i--) {
		n_conv[i - 1] = '0' + (n % base);
		n /= base;
	}
}

int main(void) {
	unsigned int n, base;
	if (scanf("%u%u", &n, &base) != 2)
		return 1;
	const size_t s = (size_t)(log(n) / log(base)) + 2;
	char n_conv[s];
	from_dec(n_conv, s, n, base);
	printf("%s\n", n_conv);
	return 0;
}
