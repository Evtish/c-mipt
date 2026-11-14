// Problem PF -- простые числа, подобные числам Фибоначчи
//
// Некоторые числа Фибоначчи, например 5 и 13 являются также простыми числами
//
// Поскольку многие числа Фибоначчи довольно велики (например 99194853094755497
// и даже 2880067194370816120 вполне входят в 64 бита), проверить их на простоту
// прямой проверкой может быть нелегко, а памяти на решето не хватит. Поэтому
// можно использовать статистические тесты из прошлых упражнений (такие как тест
// Ферма). Но для маленьких чисел простая проверка все ещё эффективней
//
// Разумеется, список простых чисел Фибоначчи не слишком интересен, его легко
// нагуглить
//
// 2, 3, 5, 13, 89, 233, 1597, 28657, 514229, 433494437, 2971215073,
// 99194853094755497, ....
//
// К счастью, в мире много других интересных последовательностей, похожих на
// числа Фибоначчи, например такая:
//
// Seq0 = 0
//
// Seq1 = 1
//
// Seqi = k * Seqi - 1 + n * Seqi - 2
//
// Ваша задача, получив на вход числа k и n вычислить самое большое простое
// число P, такое, что P < 260 и P входит в данную последовательность
//
// Вы можете быть уверены, что k и n целые, положительные и не слишком большие
// (меньше чем 256 каждое)
//
// Посылка должна состоять из программы, считывающей со стандартного ввода k и n
// и выводящей на стандартный вывод P
//
// Вполне может быть и так, что в последовательности нет простых чисел. Тогда вы
// должны вывести на стандартный вывод 0

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FERMAT_TEST_N 100
#define P_MAX ((1ULL << 60) - 1)

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
		if (exp & 1ULL) {
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

unsigned long long get_max_seq_prob_prime(unsigned char k, unsigned char n) {
	unsigned long long tmp, a = 0, b = 1, res = 0;
	assert(k > 0 && n > 0);
	while (b <= P_MAX) {
		tmp = b;
		b = k * b + n * a;
		a = tmp;
		if (is_probable_prime(b))
			res = b;
	}
	return res;
}

int main(void) {
	unsigned char k, n;
	srand(time(NULL));
	if (scanf("%hhu%hhu", &k, &n) != 2 || k < 1 || n < 1) {
		fputs("Invalid input. Input two positive integers\n", stderr);
		return EXIT_FAILURE;
	}
	printf("%llu\n", get_max_seq_prob_prime(k, n));
	return EXIT_SUCCESS;
}
