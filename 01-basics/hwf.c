// Домашнее задание HWF -- Фибоначчиевый ним
// Два игрока играют в интересную игру: изначально дано N спичек. Первый игрок
// берёт любое количество, но не все сразу спички. Теперь второй может взять не
// больше, чем вдвое больше чем первый. Далее первый берёт не больше чем вдвое
// больше второго. И так далее. Выигрывает тот, кто взял последнюю спичку
//
// Партия 1:
// 11 спичек. Первый берёт 4, второй может взять до 8 и берёт 7, победа. Запись
// партии: 11.4,7! Партия 2: 11.3,3,5! Партия 3: 11.3.2.1.1.1.1.2!

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

unsigned int lowest_fib_digit(unsigned int x) {
	if (x <= 1)
		return x;
	assert(x >= 1);
	const double sqrt5 = sqrt(5.0);
	// https://en.wikipedia.org/wiki/Fibonacci_sequence#Computation_by_rounding
	size_t n = (size_t)(log(x * sqrt5 + 0.5) / log((1.0 + sqrt5) / 2.0)) - 1;
	unsigned int lowest_dig = 0, fibs[n];
	fibs[0] = 1;
	fibs[1] = 2;
	for (size_t i = 2; i < n; i++)
		fibs[i] = fibs[i - 1] + fibs[i - 2];
	while (n > 0) {
		n--;
		if (fibs[n] <= x) {
			lowest_dig = fibs[n];
			x -= fibs[n];
		}
	}
	return lowest_dig;
}

unsigned int next_turn(unsigned int total, unsigned int possible) {
	unsigned int lfd;
	assert(0 < possible && possible <= total);
	if (possible == total) // Final turn
		return possible;
	lfd = lowest_fib_digit(total);
	if (lfd == total) // If total is a Fibonacci number
		return 1;
	return lfd <= possible ? lfd : 1;
}

int main(void) {
	unsigned int total, possible;
	if (scanf("%u%u", &total, &possible) != 2 || possible <= 0 ||
		possible >= total) {
		return 1;
	}
	printf("%u\n", next_turn(total, possible));
	return 0;
}
