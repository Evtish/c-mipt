#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

#define MF_LEN 4

void matrix_mult_mod_2x2(int32_t res[MF_LEN], int32_t a[MF_LEN],
						 int32_t b[MF_LEN]) {
	res[0] = a[0] * b[0] + a[1] * b[2];
	res[1] = a[0] * b[1] + a[1] * b[3];
	res[2] = a[2] * b[0] + a[3] * b[2];
	res[3] = a[2] * b[1] + a[3] * b[3];
}

int main(void) {
	int32_t a[MF_LEN] = {5, 3, 45, -564}, b[MF_LEN] = {565, 7, 0, 555},
			res[MF_LEN];
	matrix_mult_mod_2x2(res, a, b);
	for (size_t i = 0; i < MF_LEN; i++) {
		printf("%" PRId32, res[i]);
		if (i < MF_LEN - 1)
			fputc(' ', stdout);
		else
			fputc('\n', stdout);
	}
	return 0;
}
