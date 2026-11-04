// Problem LM -- наименьшее общее кратное
// Число 2520 является наименьшим числом, которое делится без остатка на числа
// от 2 до 10 Задача состоит в том, чтобы найти наименьшее число, которое
// делится без остатка на числа от 2 до N Посылка должна состоять из программы,
// считывающей со стандартного ввода число N и выводящей на стандартный вывод
// наименьшее общее кратное чисел от 2 до N включительно Используйте тот факт,
// что lcm(a, b) == a * b / gcd(a, b)

#include <assert.h>
#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
	unsigned long long tmp;
	while (b != 0llu) {
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

unsigned long long lcm(unsigned long long a, unsigned long long b) {
	return a * b / gcd(a, b);
}

unsigned long long lm(unsigned int n) {
	unsigned int i;
	unsigned long long res = 2llu;
	assert(n >= 2);
	for (i = 3; i <= n; ++i) {
		res = lcm(res, i);
	}
	return res;
}

int main(void) {
	unsigned int n;
	if (scanf("%u", &n) != 1 || n < 2) {
		fprintf(stderr, "Invalid input. Input one integer >= 2\n");
		return 1;
	}
	printf("%llu\n", lm(n));
	return 0;
}
