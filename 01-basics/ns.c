#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(unsigned int *a, unsigned int *b) {
	if (scanf("%u%u", a, b) != 2)
		abort();
}

// unsigned int from_dec2(unsigned int n, unsigned int base) {
// 	unsigned int n_conv = 0;
// 	for (unsigned int i = 1; n > 0; i *= 10) {
// 		n_conv = (n % base) * i + n_conv;
// 		n /= base;
// 	}
// 	return n_conv;
// }

void from_dec(char *n_conv, unsigned int n, unsigned int base) {
	for (unsigned int i = 0; n > 0; i++) {
		memmove(n_conv + 1, n_conv, i);
		n_conv[0] = '0' + (n % base);
		n /= base;
	}
}

int main(void) {
	unsigned int n, base;
	read_input(&n, &base);
	char n_conv[32] = "";
	from_dec(n_conv, n, base);
	printf("%s\n", n_conv);
	return 0;
}
