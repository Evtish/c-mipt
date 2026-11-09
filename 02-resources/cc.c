// Problem СС -- циркулярные простые
// Число 197 называется циркулярным простым, поскольку простыми являются все
// циклические перестановки его разрядов: 197 -> 971 -> 719
//
// Необходимо для заданного числа N определить ближайшее к нему циркулярное
// простое. Например для числа 200 ближайшим циркулярным простым будет 197
//
// Посылка должна состоять из программы, считывающей со стандартного ввода число
// N и выводящей на стандартный вывод ближайшее к нему циркулярное простое число
// P
//
// Вы можете предполагать, что N < 10**6

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

long long llpow(long long base, unsigned char exp) {
	long long res = 1, mult = base;
	while (exp > 0) {
		if (exp & 1u)
			res = mult * res;
		exp >>= 1;
		mult *= mult;
	}
	return res;
}

int is_prime(long long n) {
	long long i;
	if (n < 2)
		return 0;
	else if (n == 2)
		return 1;
	for (i = 2; i * i <= n; ++i) {
		if ((n % i) == 0)
			return 0;
	}
	return 1;
}

int is_circular_prime(int n) {
	unsigned char i, digit_cnt;
	long long circ_n;
	if (n < 2)
		return 0;
	digit_cnt = (unsigned char)log10(n) + 1;
	i = 0;
	circ_n = (long long)n;
	while (1) {
		if (!is_prime(circ_n))
			return 0;
		if ((++i) >= digit_cnt)
			break;
		circ_n = (circ_n % 10) * llpow(10, digit_cnt - 1) + circ_n / 10;
		if (circ_n == n)
			break;
	}
	return 1;
}

#if 1
int closest_circular_prime(int n) {
	unsigned int i;
	if (n <= 2)
		return 2;
	else if (is_circular_prime(n))
		return n;
	for (i = 0; i < (unsigned int)INT_MAX - INT_MIN; ++i) {
		if (n + i < INT_MAX && is_circular_prime(n + i + 1))
			return n + i + 1;
		else if (n - i - 1 >= 2 && is_circular_prime(n - i - 1))
			return n - i - 1;
	}
	return -1;
}
#else
int closest_circular_prime(int n) {
	int i;
	if (n <= 2)
		return 2;
	else if (is_circular_prime(n))
		return n;
	for (i = 1; n + i > n || n - i < n; i++) {
		// n + i > n becomes i > 0 due to optimizations (because signed integer
		// overflow is UB)
		if (n + i > n && is_circular_prime(n + i))
			return n + i;
		else if (n - i >= 2 && is_circular_prime(n - i))
			return n - i;
	}
	return -1;
}
#endif

int main(void) {
	int n;
	if (scanf("%d", &n) != 1) {
		fprintf(stderr, "Invalid input. Input one integer\n");
		return 1;
	}
	printf("%d\n", closest_circular_prime(n));
	return 0;
}
