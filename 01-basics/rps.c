#include <assert.h>
#include <stdio.h>

int pow_mod(int base, int exp, int mod) {
	assert(exp >= 0);
	assert(mod != 0);
	int res = 1, mult = base % mod;
	while (exp) {
		if (exp & 1)
			res = (mult * res) % mod;
		exp >>= 1;
		mult = (mult * mult) % mod;
	}
	return res;
}

// TODO: Use Euler's theorem
int spow_mod(int base, int exp, int mod) {
	assert(exp >= 0);
	assert(mod != 0);
	int res = base % mod;
	while (exp > 0) {
		res = pow_mod(res, exp, mod);
		exp--;
	}
	return res;
}

int main(void) {
	int base, exp, mod;
	if (scanf("%d%d%d", &base, &exp, &mod) != 3 || exp < 0 || mod == 0)
		return 1;
	printf("%d\n", spow_mod(base, exp, mod));
	return 0;
}
