// Problem PN -- N-е простое число
// Первым простым числом является 2, шестым является 13
// Задача заключается в том, чтобы вычислить N-e простое число
// Посылка должна состоять из программы, считывающей со стандартного ввода число
// N и выводящей на стандартный вывод N-e простое

#include <assert.h>
#include <stdio.h>

unsigned char is_prime(unsigned int a) {
	if (a < 2)
		return 0;
	for (unsigned int i = 2; i * i <= a; ++i) {
		if (a % i == 0)
			return 0;
	}
	return 1;
}

unsigned int get_nth_prime(unsigned int n) {
	unsigned int cnt = 1, number = 2;
	assert(n > 0);
	while (cnt < n) {
		if (is_prime(++number))
			cnt++;
	}
	return number;
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1 || n < 1)
		return 1;
	printf("%u\n", get_nth_prime(n));
	return 0;
}
