// Problem SF -- система чисел Фибоначчи
// Дано положительное число x, не больше чем 2^31-1 (обычный int на большинстве
// систем) Необходимо найти его единственное представление суммой чисел
// Фибоначчи если запретить в представлении две единицы рядом Посылка должна
// состоять из программы, считывающей со стандартного ввода число x и выводящей
// на стандартный вывод единицы и нули без пробелов Единица в позиции n
// означает, что fib(n) входит в сумму Возможно вы захотите мемоизировать числа
// Фибоначчи чтобы быстро искать ближайшее число Фибоначчи (как 28657 для 30987)

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>

void fib_system(int32_t x) {
	assert(x >= 0);
	if (x <= 1) {
		printf("%" PRIi32 "\n", x);
		return;
	}
	assert(x >= 1);
	const double sqrt5 = sqrt(5.0);
	// https://en.wikipedia.org/wiki/Fibonacci_sequence#Computation_by_rounding
	size_t n = (size_t)(log(x * sqrt5 + 0.5) / log((1.0 + sqrt5) / 2.0)) - 1;
	int8_t was_digit_used = 0;
	int32_t fibs[n];
	fibs[0] = 1;
	fibs[1] = 2;
	for (size_t i = 2; i < n; i++)
		fibs[i] = fibs[i - 1] + fibs[i - 2];
	while (n > 0) {
		n--;
		if (!was_digit_used && fibs[n] <= x) {
			was_digit_used = 1;
			x -= fibs[n];
		} else
			was_digit_used = 0;
		fputc(was_digit_used ? '1' : '0', stdout);
	}
	fputc('\n', stdout);
}

int main(void) {
	int32_t x;
	if (scanf("%" PRIi32, &x) != 1 || x < 0) {
		fprintf(stderr, "Invalid input. Input one non-negative number.\n");
		return 1;
	}
	fib_system(x);
	return 0;
}
