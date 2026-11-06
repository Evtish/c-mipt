#include <stdio.h>

int main(void) {
	int i = 47000, a = -79, b = 1601;
	int p0 = i * i + a * i + b;
	long long p1 = i * i + a * i + b;
	long long p2 = (long long)i * i + a * i + b;
	long long p3 = (long long)i * i + (long long)a * i + b;
	long long p4 = (long long)i * i + (long long)a * i + (long long)b;
	long long p5 = (long long)i * (long long)i + (long long)a * (long long)i +
				   (long long)b;
	printf("%d %lld %lld %lld %lld %lld\n", p0, p1, p2, p3, p4, p5);
	return 0;
}
