// Problem PP -- периоды Пизано
// Дано целое положительное число x
// Будем обозначать fib(x) = число Фибоначчи под номером x
// fib(0) = 0
// fib(1) = 1
// fib(91) = 4660046610375530309
// Будем обозначать piz(m) = период Пизано для модуля m
// piz(0) = 0
// piz(1) = 1
// piz(10) = 60
// Вам необходимо написать программу, которая вычисляет fib(x) по модулю m и
// длину периода Пизано для модуля m Посылка должна состоять из программы,
// считывающей со стандартного ввода два числа x и m и выводящей на стандартный
// вывод два числа: fib(x) mod m и piz(m)

#include <assert.h>
#include <stdio.h>

unsigned int pisano_len(unsigned long long m) {
	unsigned long long i;
	unsigned int a = 0, b = 1, tmp;
	if (m < 2ULL)
		return m;
	for (i = 2ULL; i < m * m; i++) {
		tmp = a % m;
		a = (a + b) % m;
		b = tmp;
		if (a == 0 && b == 1)
			break;
	}
	return i - 1;
}

unsigned int fib_mod(unsigned long long n, unsigned long long m) {
	unsigned int a = 0, b = 1, tmp;
	assert(m != 0ULL);
#ifndef CONTEST
	n %= pisano_len(m);
#endif
	while (n) {
		tmp = a % m;
		a = (a + b) % m;
		b = tmp;
		n--;
	}
	return a;
}

int main(void) {
	unsigned long long n, m;
#ifdef CONTEST
	unsigned int pis;
#endif
	if (scanf("%llu%llu", &n, &m) != 2 || m == 0ULL)
		return 1;
#ifdef CONTEST
	pis = pisano_len(m);
	n %= pis;
	printf("%u %u\n", fib_mod(n, m), pis);
#else
	printf("%u\n", fib_mod(n, m));
#endif
	return 0;
}
