#include <assert.h>
#include <stdio.h>

// Source - https://stackoverflow.com/a/101613
int ipow(int base, int exp) {
	assert(exp >= 0);
	int res = 1;
	while (exp) {
		if (exp & 1)
			res *= base;
		exp >>= 1;
		base *= base;
	}
	return res;
}

int main(void) {
	int base, exp;
	if (scanf("%d%d", &base, &exp) != 2 || exp < 0)
		return 1;
	printf("%d\n", ipow(base, exp));
	return 0;
}
