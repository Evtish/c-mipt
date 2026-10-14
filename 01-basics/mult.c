#include <assert.h>
#include <limits.h>
#include <stdio.h>

long long mult(long long a, long long b) {
	assert(ULLONG_MAX > LLONG_MAX); // Or else taking an absolute value of the
									// minimum will overflow
	long long res = 0LL;
	unsigned long long a_fmt, b_fmt = (unsigned long long)b;
	if (a < 0LL && b < 0LL)
		a_fmt = (unsigned long long)a;
	else
		a_fmt = a;
	while (b_fmt) {
		if (b_fmt & 1LL)
			res += a_fmt;
		b_fmt >>= 1;
		a_fmt *= 2LL;
	}
	return res;
}

int main(void) {
	long long a, b;
	if (scanf("%lld%lld", &a, &b) != 2)
		return 1;
	printf("%lld\n", mult(a, b));
	return 0;
}
