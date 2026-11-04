// Problem PS -- снова N-е простое
// Вам заранее задан тип данных решета
// Ваша задача написать две функции с заданными наперёд именами и прототипами:
// fill_sieve и nth_prime Функция fill_sieve заполняет решето, при этом
// инверсный признак хранится в каждом байте, то есть после работы этой функции
// sv->s[2] == 0, sv->s[3] == 0, sv->s[4] == 1 и т.д. Считайте, что на входе
// sv->n уже выставлено и sv->s уже аллоцировано не менее, чем в sv->n байт и
// инициализировано нулями. Выделения памяти в этой функции не происходит
// Функция nth_prime ищет N-е простое число (первым является 2, шестым 13)
// используя решето s Предполагается, что решето корректно заполнено как минимум
// до N(logN + loglogN) предыдущей функцией Посылка должна состоять из этих двух
// функций (допустимо также любое количество вспомогательных), и не должна
// содержать функцию main

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#ifndef CONTEST
#include <errno.h>
#include <stdio.h>

struct sieve_t {
	int a, b;
	unsigned char *s;
};
#endif

int get_lower_bound(int a) {
	double log_N;
	assert(a > 0);
	log_N = log((double)a);
	return a * (int)round(log_N + log(log_N) - 1.0);
}

int get_upper_bound(int b) {
	double log_N;
	assert(b > 0);
	log_N = log((double)b);
	return b * (int)round(log_N + log(log_N));
}

int init_sieve(struct sieve_t *sv, int a, int b) {
	assert(b >= a);
	sv->a = a;
	sv->b = b;
	sv->s = calloc(b - a + 1, sizeof *(sv->s));
	return (sv->s) ? 1 : 0;
}

void fill_sieve(struct sieve_t *sv) {
	int i, j;
	for (i = sv->a + 2; i * i < sv->b + 2; i++) {
		if (sv->s[i - 2])
			continue;
		for (j = i * i; j < sv->b + 2; j += i)
			sv->s[j - 2] = 1;
	}
}

int nth_prime(struct sieve_t *sv, int n) {
	int i, cnt = 0;
	assert(n <= sv->b - sv->a + 1);
	for (i = 0; cnt < n; i++) {
		if (!sv->s[i])
			cnt++;
	}
	return i + 1;
}

void free_sieve(struct sieve_t *sv) {
	free(sv->s);
	sv->a = 0;
	sv->b = 0;
	sv->s = NULL;
}

#ifndef CONTEST
int main(void) {
	int n, errsv;
	struct sieve_t sv;
	if (scanf("%d", &n) != 1 || n < 2) {
		fprintf(stderr, "Invalid input. Input one integer > 1\n");
		return 1;
	}
	if (!init_sieve(&sv, get_lower_bound(n), get_upper_bound(n))) {
		errsv = errno;
		perror("init_sieve");
		return errsv;
	}
	fill_sieve(&sv);
	printf("%d\n", nth_prime(&sv, n));
	free_sieve(&sv);
	return 0;
}
#endif
