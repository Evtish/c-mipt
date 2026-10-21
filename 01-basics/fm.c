// Problem FM -- вычисления по любому модулю
// Дано целое положительное число x и целый положительный модуль m
// Будем обозначать fib(x) = число Фибоначчи под номером x
// fib(0) = 0
// fib(1) = 1
// fib(90) = 2880067194370816120
// Вам необходимо написать программу, которая вычисляет fib(x) по модулю m
// Посылка должна состоять из программы, считывающей со стандартного ввода два
// числа x и m и выводящей на стандартный вывод число fib(x) mod m

#include <assert.h>
#include <stdio.h>

unsigned int fib_mod(unsigned int n, unsigned int m) {
	unsigned int a = 0, b = 1, tmp;
	assert(m != 0);
	while (n) {
		tmp = a % m;
		a = (a + b) % m;
		b = tmp;
		n--;
	}
	return a;
}

int main(void) {
	unsigned int n, m;
	if (scanf("%u%u", &n, &m) != 2 || m == 0)
		return 1;
	printf("%u\n", fib_mod(n, m));
	return 0;
}
