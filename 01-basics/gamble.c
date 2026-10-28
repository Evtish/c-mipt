#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATCHES_MIN 7
#define MATCHES_MAX 100

// Return a random integer between r_min and r_max inclusive.
int randint(int r_min, int r_max) {
	int r, r_range;
	if (r_min == r_max)
		return r_min;
	if (r_min == 0 && r_max == RAND_MAX)
		return rand();
	r_range = r_max - r_min + 1;
	assert(r_range > 0);
	do {
		r = rand();
	} while (r >= (RAND_MAX - RAND_MAX % r_range)); // Prevent modulo bias
	return r % r_range + r_min;
}

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
#if 1
	// Use random unstead of just 1 for variety
	unsigned int lfd;
	assert(0 < possible && possible <= total);
	if (possible == total) // Final turn
		return possible;
	lfd = lowest_fib_digit(total);
	if (lfd == total) { // If total is a Fibonacci number
		// Limit so we wouldn't lose on the second turn
		return randint(1, possible / 3 - (possible % 3 == 0));
	}
	return lfd <= possible ? lfd : (unsigned int)randint(1, possible);
#else
	unsigned int lfd;
	assert(0 < possible && possible <= total);
	if (possible == total) // Final turn
		return possible;
	lfd = lowest_fib_digit(total);
	if (lfd == total) // If total is a Fibonacci number
		return 1;
	return lfd <= possible ? lfd : 1;
#endif
}

int main(void) {
	bool is_user_turn;
	unsigned int total, possible, taken;
	srand(time(NULL));
	is_user_turn = randint(0, 1);
	total = randint(MATCHES_MIN, MATCHES_MAX);
	possible = total - 1;
	printf(
		"Ты играешь против компьютера в игру. На столе лежат несколько спичек. "
		"Первый игрок берёт любое количество, но не все спички сразу. Теперь "
		"второй может взять не больше, чем вдвое больше чем первый. Далее "
		"первый берёт не больше чем вдвое больше второго. И так далее. "
		"Выигрывает тот, кто взял последнюю спичку.\nПервый игрок: %s.\n",
		is_user_turn ? "ты" : "компьютер");
	while (1) {
		printf("Всего спичек: %u.\n", total);
		if (is_user_turn) {
			printf("Твой ход. Напиши, сколько спичек ты берёшь. От 1 до %u "
				   "включительно (0 - выход): ",
				   possible);
			if (scanf("%u", &taken) != 1 || taken > possible) {
				printf("Столько спичек взять нельзя. Читать научись.\n");
				is_user_turn = false;
				break;
			}
			if (taken == 0) {
				printf("Слит.\n");
				is_user_turn = false;
				break;
			}
		} else {
			taken = next_turn(total, possible);
			printf("Ход компьютера... Компьютер взял спичек: %u.\n", taken);
		}
		total -= taken;
		if (total <= 0)
			break;
#if 1
		possible = 2 * taken < total ? 2 * taken : total;
#else
		if (2 * taken < total) {
			possible = 2 * taken;
		} else {
			possible = total > 2 ? total - 1 : total;
		}
#endif
		is_user_turn = !is_user_turn;
	}
	if (is_user_turn) {
		printf("Ты... победил!\n");
	} else {
		printf("Ты... проиграл!\n");
	}
	return 0;
}
