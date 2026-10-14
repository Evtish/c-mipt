#include <assert.h>
#include <stdio.h>

long long pow_mod(long long base, long long exp, long long mod) {
#ifdef NAIVE
	assert(exp >= 0LL);
	assert(mod != 0LL);
	long long res = 1LL, mult = base % mod;
	while (exp) {
		res = (res * mult) % mod;
		exp--;
	}
	return res;
#else
	assert(exp >= 0LL);
	assert(mod != 0LL);
	long long res = 1LL, mult = base % mod;
	while (exp) {
		if (exp & 1LL)
			res = (res * mult) % mod;
		exp >>= 1;
		mult = (mult * mult) % mod;
	}
	return res;
#endif
}

int main(void) {
	long long base, exp, mod;
	if (scanf("%lld%lld%lld", &base, &exp, &mod) != 3 || exp < 0LL ||
		mod == 0LL)
		return 1;
	printf("%lld\n", pow_mod(base, exp, mod));
	return 0;
}
