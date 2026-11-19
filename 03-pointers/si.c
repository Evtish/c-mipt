// Problem SI — сортировка вставками
//
// Основная часть алгоритма сортировки вставками выглядит следующим образом
//
// void inssort(int *arr, int len) {
//   int i;
//   for (i = 0; i < len; ++i) {
//     int key, pos;
//     key = arr[i];
//     pos = moveright(arr, key, i);
//     arr[pos] = key;
//   }
// }
//
// Использованная здесь процедура moveright сдвигает к младшим адресам текущий
// ключ от позиции i к той позиции, которую он должен занять. Сама вставка на
// вычисленную позицию происходит после неё
//
// Ваша задача написать эту функцию с заранее заданной сигнатурой
//
// int moveright(int *arr, int key, int last) {
//   // TODO: ваш код здесь
// }
//
// Здесь arr это указатель на первый элемент массива, key это ключ, позиция для
// которого ищется, last это позиция ключа (или иначе первая позиция за
// последним отсортированным элементом). Функция возвращает позицию вставки
// ключа. На этой позиции должно остаться то значение, с которого началось
// распространение вправо
//
// Посылка должна состоять из этой одной функции (допустимо также любое
// количество вспомогательных), и не должна содержать функцию main

#include <stdio.h>
#include <stdlib.h>

static void swap(int *const pa, int *const pb) {
	if (*pa == *pb)
		return;
	*pa ^= *pb;
	*pb ^= *pa;
	*pa ^= *pb;
}

static int moveright(int *arr, int key, int last) {
	for (int i = last - 1; i >= 0; --i) {
		if (arr[i] > key) {
#if 1
			swap(arr + i, arr + last);
#endif
			last--;
		} else {
			return i + 1;
		}
	}
	return 0;
}

void inssort(int *arr, int len) {
	int i;
	for (i = 0; i < len; ++i) {
		int key, pos;
		key = arr[i];
		pos = moveright(arr, key, i);
		arr[pos] = key;
	}
}

int main(void) {
	int *arr, len, unsorted_start, i;

	if (scanf("%d", &len) != 1 || len < 1) {
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

	if (scanf("%d", &unsorted_start) != 1 || unsorted_start < 0 ||
		unsorted_start >= len) {
		fputs("Invalid start of unsorted area. Input one non-negative integer "
			  "less than the length\n",
			  stderr);
		return 1;
	}

	inssort(arr, unsorted_start + 1);

	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	fputc('\n', stdout);

	free(arr);
	return 0;
}
