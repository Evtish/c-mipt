// Problem SSE — сортировка выбором
//
// Сортировка выбором использует линейный поиск в несортированной части массива
// и обмен с подходящим значением в сортированной части. Пожалуй это один из
// самых интуитивных алгоритмов
//
// Ваша задача здесь реализовать одну итерацию сортировки выбором, то есть
// увеличение на один упорядоченной части массива с одним обменом
//
// Посылка должна состоять из программы, считывающей со стандартного ввода длину
// массива, его сам элемент за элементом и последнюю позицию отсортированной
// части. Далее программа должна делать одну итерацию сортировки выбором и
// выводить на стандартный вывод массив после этой итерации

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *const pa, int *const pb) {
	if (*pa == *pb)
		return;
	*pa ^= *pb;
	*pb ^= *pa;
	*pa ^= *pb;
}

void selsort_step(int *const arr, size_t len, size_t unsorted_start) {
	size_t min_idx = unsorted_start;
	assert(unsorted_start < len);
	for (size_t i = unsorted_start + 1; i < len; ++i) {
		if (arr[i] < arr[min_idx]) {
			min_idx = i;
		}
	}
	swap(arr + unsorted_start, arr + min_idx);
}

int main(void) {
	int *arr;
	size_t len, unsorted_start, i;

	if (scanf("%zu", &len) != 1 || len < 1) {
		fputs("Invalid length. Input one positive integer\n", stderr);
		return 1;
	}

	if (!(arr = calloc(len, sizeof(*arr)))) {
		perror("calloc");
		return 1;
	}

	for (i = 0; i < len; ++i) {
		if (scanf("%d", arr + i) != 1) {
			fputs("Invalid array element. Input one integer\n", stderr);
			return 1;
		}
	}

	if (scanf("%zu", &unsorted_start) != 1 || unsorted_start >= len) {
		fputs("Invalid start of unsorted area. Input one positive integer less "
			  "than the length\n",
			  stderr);
		return 1;
	}

	selsort_step(arr, len, unsorted_start);

	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	fputc('\n', stdout);

	free(arr);
	return 0;
}
