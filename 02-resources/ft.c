// Problem FT -- тест Ферма
//
// Малая теорема Ферма
//
// prime p, gcd(a, p) == 1 = > a ^ (p - 1) = 1 (mod p)
//
// Может быть использована для быстрой проверки простоты числа p: если удаётся
// найти свидетеля, то есть такое число a, что a(p - 1) != 1 (mod p), это
// автоматически значит, что число составное
//
// Увы, в качестве свидетеля подходит не каждое число. Например для числа 221,
// число 38 удовлетворяет условиям теоремы Ферма, тем не менее число 221
// составное. Такие числа, как 38 называются лжецами для числа 221
//
// Ваша задача реализовать тест Ферма для чисел, меньших, чем 264 - 1 (unsigned
// long long)
//
// Посылка должна состоять из программы, считывающей со стандартного ввода число
// P и выводящей на стандартный вывод 1, если оно простое и 0, если нет
//
// Свидетеля можно искать перебором или пробовать случайные числа. Здесь есть
// элемент творческой неопределённости. Некоторые числа (т.н. числа Кармайкла),
// являясь составными, вообще не имеют свидетелей, но шансы натолкнуться на них
// довольно малы и ответ 1 для этих чисел в этой задаче будет правильным
//
// Все входные числа > 108, так что вы можете даже не пробовать решето или
// проверку в лоб. Все входные числа < 264 и все они положительны, поэтому
// использовать тип unsigned long long будет хорошей идеей
//
// В примерах указана факторизация, но написать тест Ферма куда проще, чем
// факторизацию

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FERMAT_TEST_N 100

// Return a random integer between r_min and r_max inclusive
int randint(int r_min, int r_max) {
	int r, r_range;
	assert(r_max >= r_min);
	if (r_min == r_max)
		return r_min;
	if (r_min == 0 && r_max == RAND_MAX)
		return rand();
	r_range = r_max - r_min + 1;
	do {
		r = rand();
	} while (r >= (RAND_MAX - RAND_MAX % r_range)); // Prevent modulo bias
	return r % r_range + r_min;
}

unsigned long long pow_mod(unsigned int base, unsigned long long exp,
						   unsigned long long mod) {
	unsigned long long res, mult;
	assert(mod != 0);
	res = 1;
	mult = base % mod;
	while (exp) {
		if (exp & 1llu) {
			assert(res <= ULLONG_MAX / mult);
			res = (res * mult) % mod;
		}
		exp >>= 1;
		// TODO: Fix overflow for mod == 187488898057
		assert(mult <= ULLONG_MAX / mult);
		mult = (mult * mult) % mod;
	}
	return res;
}

int is_probable_prime(unsigned long long p) {
	unsigned int a, i;
	if (p <= 1)
		return 0;
	else if (p <= 3)
		return 1;
	for (i = 0; i < FERMAT_TEST_N; ++i) {
		a = randint(2, (p - 2 > RAND_MAX) ? RAND_MAX : p - 2);
		assert(1 < a && a < p - 1);
		if (pow_mod(a, p - 1, p) != 1)
			return 0;
	}
	return 1;
}

int main(void) {
	unsigned long long p;
	srand(time(NULL));
	if (scanf("%llu", &p) != 1) {
		fputs("Invalid input. Input one non-negative integer\n", stderr);
		return EXIT_FAILURE;
	}
	printf("%d\n", is_probable_prime(p));
	return EXIT_SUCCESS;
}
