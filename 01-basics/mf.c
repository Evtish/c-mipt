// Problem MF -- матрицы Фибоначчи
// В этом упражнении вам надо будет возводить матрицы 2x2 в степени по модулю m
// Дано: четыре положительных числа x00, x01, x10, x11 а также целые
// положительные числа n и m. Все числа не превышают числа 2^31 - 1 Матрица
// формируется в row-major order, т.е. следующим образом: x00 x01 x10 x11
// Необходимо: быстро возвести матрицу X в степень n по модулю m
// Посылка должна состоять из программы, считывающей со стандартного ввода шесть
// чисел x00, x01, x10, x11, n и m и выводящей на стандартный вывод четыре числа
// x00, x01, x10, x11
//
// Пример 1 (матрица Фибоначчи):
// Вход: 1 1 1 0 20 10
// Выход: 6 5 5 1
// Пример 2 (снова матрица Фибоначчи):
// Вход: 1 1 1 0 20000 64
// Выход: 34 5 5 29
// Пример 2 (не матрица Фибоначчи):
// Вход: 1 2 3 0 20000 64
// Выход: 39 26 39 26

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MF_LEN (size_t)4

int32_t mult_mod(int32_t a, int32_t b, int32_t mod) {
	assert(mod != 0);
	return (a % mod * b % mod) % mod;
}

int32_t add_mod(int32_t a, int32_t b, int32_t mod) {
	assert(mod != 0);
	return (a % mod + b % mod) % mod;
}

void matrix_mult_mod_2x2(int32_t res[MF_LEN], int32_t a[MF_LEN],
						 int32_t b[MF_LEN], int32_t mod) {
	assert(mod != 0);
	res[0] = add_mod(mult_mod(a[0], b[0], mod), mult_mod(a[1], b[2], mod), mod);
	res[1] = add_mod(mult_mod(a[0], b[1], mod), mult_mod(a[1], b[3], mod), mod);
	res[2] = add_mod(mult_mod(a[2], b[0], mod), mult_mod(a[3], b[2], mod), mod);
	res[3] = add_mod(mult_mod(a[2], b[1], mod), mult_mod(a[3], b[3], mod), mod);
}

void matrix_pow_mod_2x2(int32_t res[MF_LEN], int32_t a[MF_LEN], uint32_t exp,
						int32_t mod) {
	int32_t mult[MF_LEN], tmp[MF_LEN];
	assert(mod != 0);
#if 0
	if (mod == 1) {
		res[0] = 0;
		res[1] = 0;
		res[2] = 0;
		res[3] = 0;
		return;
	}
#endif
	res[0] = 1;
	res[1] = 0;
	res[2] = 0;
	res[3] = 1;
	for (size_t i = 0; i < MF_LEN; i++)
		mult[i] = a[i] % mod;
	while (1) {
		if (exp & 1u) {
			memcpy(tmp, res, MF_LEN * sizeof(*res));
			matrix_mult_mod_2x2(res, tmp, mult, mod);
		}
		exp >>= 1;
		if (exp <= 0)
			break;
		memcpy(tmp, mult, sizeof mult);
		matrix_mult_mod_2x2(mult, tmp, tmp, mod);
	}
}

int main(void) {
	int32_t res[MF_LEN], a[MF_LEN], mod;
	uint32_t exp;
	int s =
		scanf("%" SCNd32 "%" SCNd32 "%" SCNd32 "%" SCNd32 "%" SCNu32 "%" SCNd32,
			  a, a + 1, a + 2, a + 3, &exp, &mod);
	if (s != MF_LEN + 2 || mod == 0) {
		fprintf(stderr,
				"Invalid input. Input a square matrix of %zu integers, "
				"non-negative integer and non-zero integer\n",
				MF_LEN);
		return 1;
	}
	matrix_pow_mod_2x2(res, a, exp, mod);
	for (size_t i = 0; i < MF_LEN; i++) {
		printf("%" PRId32, res[i]);
		if (i < MF_LEN - 1)
			fputc(' ', stdout);
		else
			fputc('\n', stdout);
	}
	return 0;
}
