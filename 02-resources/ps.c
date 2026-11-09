// Problem PS -- снова N-е простое
// Вам заранее задан тип данных решета
//
// Ваша задача написать две функции с заданными наперёд именами и прототипами:
// fill_sieve и nth_prime
//
// Функция fill_sieve заполняет решето, при этом инверсный признак хранится в
// каждом байте, то есть после работы этой функции sv->s[2] == 0, sv->s[3] == 0,
// sv->s[4] == 1 и т.д.
//
// Считайте, что на входе sv->n уже выставлено и sv->s уже аллоцировано не
// менее, чем в sv->n байт и инициализировано нулями. Выделения памяти в этой
// функции не происходит
//
// Функция nth_prime ищет N-е простое число (первым является 2, шестым 13)
// используя решето s
//
// Предполагается, что решето корректно заполнено как минимум до N(logN +
// loglogN) предыдущей функцией
//
// Посылка должна состоять из этих двух функций (допустимо также любое
// количество вспомогательных), и не должна содержать функцию main

#include <assert.h>
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

int get_upper_bound(int N) {
	double log_N;
	assert(N > 0);
	log_N = log((double)N);
	return N * (int)round(log_N + log(log_N));
}

int init_sieve(struct sieve_t *sv, int N) {
	assert(N > 1);
	sv->n = N - 1;
	sv->s = calloc(sv->n, sizeof *(sv->s));
	return (sv->s) ? 1 : 0;
}

void fill_sieve(struct sieve_t *sv) {
	int i, j;
	for (i = 2; i * i < sv->n + 1; i++) {
		if (sv->s[i - 2])
			continue;
		for (j = i * i; j < sv->n + 1; j += i)
			sv->s[j - 2] = 1;
	}
}

int nth_prime(struct sieve_t *sv, int N) {
	int i, cnt = 0;
	assert(N <= sv->n);
	for (i = 0; cnt < N; i++) {
		if (!sv->s[i])
			cnt++;
	}
	return i + 1;
}

void free_sieve(struct sieve_t *sv) {
	free(sv->s);
	sv->n = 0;
	sv->s = NULL;
}

#ifndef CONTEST
int main(void) {
	int N, errsv;
	struct sieve_t sv;
	if (scanf("%d", &N) != 1 || N < 2) {
		fprintf(stderr, "Invalid input. Input one integer > 1\n");
		return 1;
	}
	if (!init_sieve(&sv, get_upper_bound(N))) {
		errsv = errno;
		perror("init_sieve");
		return errsv;
	}
	fill_sieve(&sv);
	printf("%d\n", nth_prime(&sv, N));
	free_sieve(&sv);
	return 0;
}
#endif
