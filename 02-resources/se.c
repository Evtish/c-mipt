// Problem SE -- количество простых чисел
// На стандартном вводе дано число n.
// Вам надо вывести на стандартный вывод количество простых чисел меньших или
// равных n.

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int count_primes(unsigned char *sieve, int n) {
	int i, j, cnt = n - 1;
	if (n < 2)
		return 0;
	sieve = calloc(n - 1, sizeof *sieve);
	if (!sieve)
		return -1;
	for (i = 2; i * i <= n; i++) {
		if (sieve[i - 2])
			continue;
		for (j = i * i; j <= n; j += i) {
			if (!sieve[j - 2]) {
				cnt--;
				sieve[j - 2] = 1;
			}
		}
	}
	return cnt;
}

int main(void) {
	unsigned char *sieve = NULL;
	int n, cnt, errsv;
	if (scanf("%d", &n) != 1) {
		fprintf(stderr, "Invalid input. Input one integer\n");
		return 1;
	}
	cnt = count_primes(sieve, n);
	if (cnt == -1) {
		errsv = errno;
		perror("count_primes");
		return errsv;
	}
	printf("%d\n", cnt);
	free(sieve);
	return 0;
}
