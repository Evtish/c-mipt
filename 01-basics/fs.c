// Problem FS -- система факториалов
// Число может быть единственным образом представлено в факториальной системе
// счисления. Пример: 463=3*5! + 4 * 4! + 1 * 3! + 0 * 2! + 1 * 1! = 34101
// Правила довольно просты: у каждого n! может быть коэффициент 0 <= k <= n
// Ваша задача написать программу которая принимает на вход положительное
// десятичное число и печатает его в факториальной системе счисления.

#include <inttypes.h>
#include <stdio.h>

#define UINT32_FACT_MAX 12

// TODO: Ensure the length of factorials array is correct
void fs(uint32_t n) {
	const size_t s = UINT32_FACT_MAX;
	size_t i;
	uint32_t factorials[s];
	for (i = 1; i < s + 1; i++) {
		if (i <= 1)
			factorials[i] = 1;
		else
			factorials[i] = i * factorials[i - 1];
		if (factorials[i] > n)
			break;
	}
	for (size_t j = (i > 1) ? i - 1 : 1; j > 0; j--) {
		uint32_t m = n / factorials[j];
		if (m != 0)
			n %= m * factorials[j];
		printf("%" PRIu32 ".", m);
	}
	fputc('\n', stdout);
}

int main(void) {
	uint32_t n;
	if (scanf("%" PRIu32, &n) != 1)
		return 1;
	fs(n);
	return 0;
}
