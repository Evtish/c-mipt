// Problem BI -- инвертировать бит
// Вам предлагается инвертировать N-й по счёту бит в массиве.
//
// На вход приходит количество чисел, каждое не больше одного байта, далее все
// эти числа и дальше номер бита.
//
// Номер бита отсчитывается от нулевого бита нулевой ячейки массива. Нулевой бит
// первой ячейки будет иметь номер 8 и т.д.
//
// Посылка должна состоять из программы, считывающей со стандартного ввода
// массив и число N и выводящей на стандартный вывод массив в котором N-й бит
// инвертирован.
//
// В случае если номер запрашиваемого бита больше максимального номера в
// массиве, массив выводится без изменений.

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int invert_bit(unsigned char *const a, const size_t len, const size_t n) {
	const size_t elem = n / CHAR_BIT, bit = n % CHAR_BIT;
	if (elem >= len)
		return 0;
	a[elem] ^= (1 << bit);
	return 1;
}

int main(void) {
	unsigned char *a;
	size_t len, i, n;
	int errsv;
	if (scanf("%zu", &len) != 1 || len < 1) {
		fprintf(stderr, "Invalid input. Input one positive integer\n");
		return 1;
	}
	a = calloc(len, sizeof(*a));
	if (!a) {
		errsv = errno;
		perror("calloc");
		return errsv;
	}
	for (i = 0; i < len; ++i) {
		if (scanf("%hhu", a + i) != 1) {
			fprintf(stderr, "Invalid input. Input one non-negative integer\n");
			return 1;
		}
	}
	if (scanf("%zu", &n) != 1) {
		fprintf(stderr, "Invalid input. Input one non-negative integer\n");
		return 1;
	}
	invert_bit(a, len, n);
	for (i = 0; i < len; ++i)
		printf("%hhu ", a[i]);
	fputc('\n', stdout);
	free(a);
	return 0;
}
