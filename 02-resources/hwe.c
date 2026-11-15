// Домашнее задание HWE — решето с радикальной экономией памяти
//
// Вам заранее задан тип данных решета
//
// struct sieve_t {
//   int n;
//   unsigned char *mod1;
//   unsigned char *mod5;
// };
//
// Здесь n это размер обоих частей решета в байтах, то есть каждый из массивов
// mod1 и mod5 содержит n байт
//
// Ваша задача написать функции fill_sieve и is_prime с наперёд заданными
// прототипами
//
// void fill_sieve(struct sieve_t *sv);
// int is_prime(struct sieve_t *sv, unsigned n);
//
// Функция fill_sieve заполняет решето, при этом признак хранится в каждом бите,
// при этом s.mod1 хранит только биты для чисел вида 6k + 1 (1 7 13 19, ...), а
// s.mod5 для чисел вида 6k + 5 (5, 11, 17, ...)
//
// То есть после работы этой функции s.mod1[0] == 0x11 (00010001), s.mod5[0] =
// 0x20 (00100000) и т.д.
//
// Выделения памяти в этой функции не происходит
//
// Функция is_prime возвращает 1 если число n простое или 0 если оно составное

#include <assert.h>
#include <limits.h>

#define SIEVE_B 6  // Should be an even number
#define SIEVE_R1 1 // Should be a comprime to SIEVE_B
#define SIEVE_R2 5 // Should be a comprime to SIEVE_B

#ifndef CONTEST
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
	unsigned char *mod1;
	unsigned char *mod5;
	int n;
};
#endif

// Should not be used by the end user.
static void fill_mod(unsigned char *mod, int len, int b, int r) {
	int i, j, m, n, upper_bound;
	assert(b != 0);
	assert(CHAR_BIT != 0);
	upper_bound = b * (len * CHAR_BIT - 1) + r;
	for (i = 0, m = b * i + r; m * m <= upper_bound; ++i, m = b * i + r) {
		assert(i / CHAR_BIT < len);
		if (mod[i / CHAR_BIT] & (1u << (i % CHAR_BIT)))
			continue;
		if (m < 2) {
			mod[i / CHAR_BIT] |= (1u << (i % CHAR_BIT));
			continue;
		}
		// TODO: Fix the loop
		for (n = m * m, j = n / b; n <= upper_bound; n += m, j = n / b) {
			assert(j / CHAR_BIT < len);
			mod[j / CHAR_BIT] |= (1u << (j % CHAR_BIT));
		}
	}
}

void fill_sieve(struct sieve_t *sv) {
	fill_mod(sv->mod1, sv->n, SIEVE_B, SIEVE_R1);
	fill_mod(sv->mod5, sv->n, SIEVE_B, SIEVE_R2);
}

int is_prime(struct sieve_t *sv, int n) {
	int q, r;
	assert(SIEVE_B != 0);
	assert(CHAR_BIT != 0);
	q = n / SIEVE_B, r = n % SIEVE_B;
	if ((r != SIEVE_R1) && (r != SIEVE_R2))
		return 0;
	if (q / CHAR_BIT + 1 > sv->n)
		return -1;
	if (r == SIEVE_R1)
		return !(sv->mod1[q / CHAR_BIT] & (1u << (q % CHAR_BIT)));
	else
		return !(sv->mod5[q / CHAR_BIT] & (1u << (q % CHAR_BIT)));
}

#ifndef CONTEST
// Should not be used by the end user.
static int get_n(int amount) {
	assert(amount > 0);
	assert(SIEVE_B != 0);
	assert(CHAR_BIT != 0);
	return (amount - 1) / SIEVE_B / CHAR_BIT + 1;
}

int init_sieve(struct sieve_t *sv, int amount) {
	if (amount < 1) {
		errno = 1;
		return -1;
	}
	sv->n = get_n(amount);
	assert(sv->n > 0);
	sv->mod1 = calloc(sv->n, sizeof *(sv->mod1));
	if (!sv->mod1)
		return -1;
	sv->mod5 = calloc(sv->n, sizeof *(sv->mod5));
	if (!sv->mod5)
		return -1;
	return 0;
}

void free_sieve(struct sieve_t *sv) {
	free(sv->mod1);
	sv->mod1 = NULL;
	free(sv->mod5);
	sv->mod5 = NULL;
	sv->n = 0;
}

int main(void) {
	int n, is_p;
	struct sieve_t sv;
	if (scanf("%d", &n) != 1 || n < 0) {
		fputs("Invalid input. Input one non-negative integer\n", stderr);
		return EXIT_FAILURE;
	}
	if (init_sieve(&sv, n + 1) == -1) {
		perror("init_sieve");
		return EXIT_FAILURE;
	}
	fill_sieve(&sv);
	is_p = is_prime(&sv, n);
	if (is_p == -1) {
		fprintf(stderr, "n = %d is too big for this sieve\n", n);
		free_sieve(&sv);
		return EXIT_FAILURE;
	}
	printf("%d\n", is_p);
	free_sieve(&sv);
	return EXIT_SUCCESS;
}
#endif
