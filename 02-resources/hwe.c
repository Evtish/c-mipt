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

#define SIEVE_B (unsigned int)6
#define SIEVE_R1 (unsigned int)1
#define SIEVE_R2 (unsigned int)5

#ifdef CONTEST
#include "u_template.h"
#else
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
	unsigned char *mod1;
	unsigned char *mod5;
	int n;
};
#endif

unsigned int get_upper_bound(int size) {
	return SIEVE_B * (size * CHAR_BIT - 1) + SIEVE_R2;
}

void fill_sieve(struct sieve_t *sv) {
	unsigned int i, iq, ir, j, jq, jr, upper_bound;
	upper_bound = get_upper_bound(sv->n);
	sv->mod1[0] |= 1u; // SIEVE_R1 == 1 is not a prime number
	for (i = 2; i * i <= upper_bound; ++i) {
		iq = i / SIEVE_B;
		ir = i % SIEVE_B;
		if ((ir == SIEVE_R1) &&
			(sv->mod1[iq / CHAR_BIT] & (1u << iq % CHAR_BIT)))
			continue;
		else if ((ir == SIEVE_R2) &&
				 (sv->mod5[iq / CHAR_BIT] & (1u << iq % CHAR_BIT)))
			continue;
		for (j = i * i; j <= upper_bound; j += i) {
			jq = j / SIEVE_B;
			jr = j % SIEVE_B;
			if (jr == SIEVE_R1)
				sv->mod1[jq / CHAR_BIT] |= (1u << (jq % CHAR_BIT));
			else if (jr == SIEVE_R2)
				sv->mod5[jq / CHAR_BIT] |= (1u << (jq % CHAR_BIT));
		}
	}
}

int is_prime(struct sieve_t *sv, unsigned int n) {
	unsigned int q, r;
	// Because SIEVE_B, SIEVE_R1 and SIEVE_R2 do not cover these primes.
	if (n == 2 || n == 3)
		return 1;
	if (n > get_upper_bound(sv->n))
		return -1;
	q = n / SIEVE_B;
	r = n % SIEVE_B;
	if ((r != SIEVE_R1) && (r != SIEVE_R2))
		return 0;
	if (r == SIEVE_R1)
		return !(sv->mod1[q / CHAR_BIT] & (1u << (q % CHAR_BIT)));
	else if (r == SIEVE_R2)
		return !(sv->mod5[q / CHAR_BIT] & (1u << (q % CHAR_BIT)));
	return -1;
}

#ifndef CONTEST
// n - non-negative number to check for primality
int get_size(unsigned int n) { return n / SIEVE_B / CHAR_BIT + 1; }

int init_sieve(struct sieve_t *sv, int size) {
	sv->n = size;
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
	unsigned int n;
	int is_p;
	struct sieve_t sv;
	if (scanf("%u", &n) != 1) {
		fputs("Invalid input. Input one non-negative integer\n", stderr);
		return EXIT_FAILURE;
	}
	if (init_sieve(&sv, get_size(n)) == -1) {
		perror("init_sieve");
		return EXIT_FAILURE;
	}
	fill_sieve(&sv);
	is_p = is_prime(&sv, n);
	if (is_p == -1) {
		fprintf(stderr, "is_prime(%u) failed\n", n);
		free_sieve(&sv);
		return EXIT_FAILURE;
	}
	printf("%d\n", is_p);
	free_sieve(&sv);
	return EXIT_SUCCESS;
}
#endif
