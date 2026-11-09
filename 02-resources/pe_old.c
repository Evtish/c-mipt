// Problem PE -- побитовое решето
//
// Вам заранее задан тип данных решета
//
// Ваша задача написать функции fill_sieve и is_prime с наперёд заданными
// прототипами
//
// Функция fill_sieve заполняет решето, при этом признак хранится в каждом бите,
// и 1 обозначает, что число составное
//
// То есть после работы этой функции s[0] == 0x53 (01010011), s[1] = 0xD7
// (11010111) и т.д.
//
// Считайте, что на входе sv->n уже выставлено и sv->s уже аллоцировано не
// менее, чем в sv->n байт и инициализировано нулями. Выделения памяти в этой
// функции не происходит
//
// Обратите внимание: sv->n это размер решета в байтах. Вы должны заполнить его
// полностью, каждый бит. До какого числа при этом идти это ваше решение, но это
// точно не число sv->n
//
// Функция is_prime проверяет число n на простоту с использованием решета sv
//
// Посылка должна состоять из этих двух функций (допустимо также любое
// количество вспомогательных), и не должна содержать функцию main

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#ifndef CONTEST
#include <errno.h>
#include <stdio.h>

struct sieve_t {
	unsigned char *s;
	int n;
};
#endif

static int get_n(int n) {
	double log_n;
	assert(n > 0);
	if (n == 1)
		return 3;
	log_n = log((double)n);
	return n * (int)round(log_n + log(log_n)) / CHAR_BIT + 1;
}

int init_sieve(struct sieve_t *sv, int n) {
	sv->n = get_n(n);
	assert(sv->n > 0);
	sv->s = calloc(sv->n, sizeof *(sv->s));
	return (sv->s) ? 1 : 0;
}

void fill_sieve(struct sieve_t *sv) {
	int i, j;
	sv->s[0] = 1u | (1u << 1);
	for (i = 2; i * i < sv->n * CHAR_BIT; i++) {
		if (sv->s[i / CHAR_BIT] & (1u << (i % CHAR_BIT)))
			continue;
		for (j = i * i; j < sv->n * CHAR_BIT; j += i)
			sv->s[j / CHAR_BIT] |= (1u << (j % CHAR_BIT));
	}
}

int nth_prime(struct sieve_t *sv, int n) {
	int i, cnt = 0;
	if (get_n(n) > sv->n)
		return -1;
	for (i = 0; cnt < n; i++) {
		if (!(sv->s[i / CHAR_BIT] & (1u << (i % CHAR_BIT))))
			cnt++;
	}
	return i - 1;
}

void free_sieve(struct sieve_t *sv) {
	free(sv->s);
	sv->n = 0;
	sv->s = NULL;
}

#ifndef CONTEST
int main(void) {
	int n, errsv, found_prime;
	struct sieve_t sv;
	if (scanf("%d", &n) != 1 || n <= 0) {
		fprintf(stderr, "Invalid input. Input one positive integer\n");
		return 1;
	}
	if (!init_sieve(&sv, n)) {
		errsv = errno;
		perror("init_sieve");
		return errsv;
	}
	fill_sieve(&sv);
	found_prime = nth_prime(&sv, n);
	if (found_prime == -1) {
		fprintf(
			stderr,
			"The prime number of index %d is too big for the current sieve.\n",
			n);
		return 1;
	}
	printf("%d\n", found_prime);
	free_sieve(&sv);
	return 0;
}
#endif
