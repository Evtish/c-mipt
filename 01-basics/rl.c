// Problem RL -- рекурсия в цикл
// Ниже приведён исходный код программы для рекурсивного алгоритма Евклида.
// Ваша задача: переписать его так, чтобы вместо рекурсии использовался цикл
// Посылка должна состоять из программы, считывающей со стандартного ввода два
// числа x и y и выводящей на стандартный вывод одно число g

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
