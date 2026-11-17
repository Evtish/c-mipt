// Problem FY — тасование массива
//
// Ваша задача -- написать программу, которая:
//
// Считывает со стандартного ввода размер массива и дальше сам массив.
//
// Печатает на стандартный вывод перетасованный массив.
//
// Для тасования используйте алгоритм Фишера-Йетса и следующую функцию myrand.
//
// int myrand() {
//   static unsigned long int seed = 1;
//   seed = seed * 1103515245 + 12345;
//   return (unsigned int)(seed / 65536) % 32768;
// }
//
// Использовать именно такую функцию необходимо чтобы ваша тасовка совпала с
// ответом в тесте.
//
// Если в массиве только один элемент, напечатайте его
//
// Если элементов нет, напечатайте "0"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef CONTEST
int myrand() {
	static unsigned long int seed = 1;
	seed = seed * 1103515245 + 12345;
	return (unsigned int)(seed / 65536) % 32768;
}
#else
#include <time.h>
#endif

// Return a random integer between r_min and r_max inclusive.
int randint(int r_min, int r_max) {
	int r, range;
	assert(r_max >= r_min);
	if (r_min == r_max)
		return r_min;
	if (r_min == 0 && r_max == RAND_MAX)
#ifdef CONTEST
		return myrand();
#else
		return rand();
#endif
	range = r_max - r_min + 1;
	do {
#ifdef CONTEST
		r = myrand();
#else
		r = rand();
#endif
	} while (r >= (RAND_MAX - RAND_MAX % range)); // To prevent modulo bias.
	return r % range + r_min;
}

void swap(int *const pa, int *const pb) {
	if (*pa == *pb)
		return;
	*pa ^= *pb;
	*pb ^= *pa;
	*pa ^= *pb;
}

void fyshuffle(int *const arr, int len) {
	int new_end_idx;
	assert(len > 0);
	while (len > 0) {
		--len;
		new_end_idx = randint(0, len);
		swap(&arr[len], &arr[new_end_idx]);
	}
}

int main(void) {
	int n, len, *arr, i;
#ifndef CONTEST
	srand(time(NULL));
#endif

	n = scanf("%d", &len);
	if (n != 1 || len < 0) {
		fputs("Invalid length. Input one non-negative integer.\n", stderr);
		return EXIT_FAILURE;
	}
	if (len <= 0) {
		puts("0");
		return EXIT_SUCCESS;
	}

	arr = calloc(len, sizeof(*arr));
	if (!arr) {
		perror("calloc");
		return EXIT_FAILURE;
	}

	for (i = 0; i < len; ++i) {
		n = scanf("%d", &arr[i]);
		if (n != 1) {
			fputs("Invalid number. Input one integer.\n", stderr);
			free(arr);
			return EXIT_FAILURE;
		}
	}

	fyshuffle(arr, len);

	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	fputc('\n', stdout);

	free(arr);
	return EXIT_SUCCESS;
}
