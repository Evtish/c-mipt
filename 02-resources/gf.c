// Problem GF -- генерирующие формулы
// Потрясающая формула n2 + n + 41, открытая Эйлером, генерирует для 0 <= n <=
// 39 положительные простые числа и только их
//
// Если не ограничиваться положительными коэффициентами, то n2 - n + 41,
// тривиально даёт на одно положительное простое больше (она начинается с 41,
// 41, и дальше полностью повторяет исходную последовательность)
//
// Ещё более потрясающая формула 36n2 − 810n + 2753 генерирует одно за другим 45
// простых (A050268)
//
// Ваша задача найти длину самой длинной последовательности положительных
// простых чисел, которую можно сгенерировать с помощью формулы n2
// + an + b, в предположеннии, что |a| < N и |b| < N
//
// Обратите внимание: эти числа не обязаны быть последовательно возрастающими
// или убывающими. Слово последовательность здесь употребляется в том смысле,
// что, начиная с n = 0, и до некоторого числа, каждое очередное число
// оказывается простым. Например 3, 17, 17, 31, 5 это последовательность из пяти
// простых
//
// Посылка должна состоять из программы, считывающей со стандартного ввода число
// N и выводящей на стандартный вывод три числа: a, b и длину наибольшей
// последовательности

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
	unsigned char *s;
	int n;
};

// Should not be used by the end user.
//
// Get the maximum possible length of a sieve for a sequence n * n + a * n + b.
//
// n = n.
// a = -1.
// b = n - 1.
// +1 because we count from 0.
// length = n * n + (-1) * n + (n - 1) + 1.
// length = n * n.
static int get_n(int n) {
	assert(n > 0);
	return n * n;
}

// Initialize sv.
//
// Returns 1 on success and 0 on failure.
int sieve_init(struct sieve_t *sv, int n) {
	sv->n = get_n(n);
	sv->s = calloc(sv->n, sizeof *(sv->s));
	return (sv->s) ? 1 : 0;
}

// Fill sv: 0 if number is prime else 1.
void sieve_fill(struct sieve_t *sv) {
	int i, j;
	sv->s[0] = 1;
	sv->s[1] = 1;
	for (i = 2; i * i < sv->n; ++i) {
		if (sv->s[i])
			continue;
		for (j = i * i; j < sv->n; j += i)
			sv->s[j] = 1;
	}
}

// Should not be used by the end user.
//
// Get the biggest prime number less or equal to n.
static int get_biggest_prime(struct sieve_t *sv, int n) {
	int i;
	assert(n < sv->n);
	i = n;
	while (i > 0) {
		if (!sv->s[i])
			break;
		i--;
	}
	return i;
}

// Free sv
void sieve_free(struct sieve_t *sv) {
	free(sv->s);
	sv->n = 0;
	sv->s = NULL;
}

// Get length of the longest sequence of primes for given a, b, n.
//
// Returns the length on success and -1 on failure (when n is too big for sv).
// If fails pa and pb will stay untouched!
//
// b is the biggest prime number < n.
// -b < a <= -1 (if -a >= b then the result will be 1 on the 2nd iteration).
int count_primes(struct sieve_t *sv, int *pa, int *pb, int n) {
	int i, p, a, b, max_len;
	if (get_n(n) > sv->n)
		return -1;
	*pa = 0;
	*pb = 0;
	max_len = 0;
	for (b = get_biggest_prime(sv, n - 1); b >= 2;
		 b = get_biggest_prime(sv, b - 1)) {
		for (a = -1; a > -b; --a) {
			for (i = 0; i <= n; ++i) {
				p = i * i + a * i + b;
				assert(p < sv->n);
				if (p < 0 || sv->s[p])
					break;
			}
			if (i > max_len) {
				*pa = a;
				*pb = b;
				max_len = i;
			}
			if (max_len >= n)
				break;
		}
	}
	return max_len;
}

int main(void) {
	int a, b, n, cnt;
	struct sieve_t sv;
	if (scanf("%d", &n) != 1 || n < 1) {
		fprintf(stderr, "Invalid input. Input one positive integer.\n");
		return 1;
	}
	if (!sieve_init(&sv, n)) {
		perror("sieve_init");
		return 1;
	}
	sieve_fill(&sv);
	cnt = count_primes(&sv, &a, &b, n);
	if (cnt == -1) {
		fprintf(stderr, "n = %d is too big for the current sieve.\n", n);
		return 1;
	}
	printf("%d %d %d\n", a, b, cnt);
	sieve_free(&sv);
	return 0;
}
