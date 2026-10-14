#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
	while (b != 0) {
		long long tmp = a;
		a = b;
		b = tmp % b;
	}
	return llabs(a);
}

int main() {
	long long a, b;
	if (scanf("%lld%lld", &a, &b) != 2 || b == 0)
		return 1;
	printf("%lld\n", gcd(a, b));
	return 0;
}
