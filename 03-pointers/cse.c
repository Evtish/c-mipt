// Problem CSE — обобщённая сортировка выбором
//
// Сортировка выбором использует линейный поиск в несортированной части массива
// и обмен с подходящим значением в сортированной части и её конкретной версии
// посвящена Problem SSE. Настало время обобщить сделанное
//
// Итерацию сортировки выбором можно сделать, обладая только информацией о
// размере элемента и функцией-компаратором. В этом задании считайте тип
// компаратора заданным заранее
//
// typedef int (*cmp_t)(void const * lhs, void const * rhs);
//
// Компаратор возвращает 1 если lhs логически меньше, чем rhs, иначе 0
//
// Ваша задача написать функцию одного шага обобщённой сортировки выбором с
// заранее заданной сигнатурой
//
// Верните 0 при успешном выполнении
//
// int selstep(void * parr, int eltsize, int numelts, int nsorted, cmp_t cmp) {
//   // TODO: реализуйте эту функцию
// }
//
// arr это массив, уже отсортированный до позиции nsorted, на этой позиции (с
// нуля) стоит первый несортированный элемент
//
// eltsize это размер элементов массива, numelts это количество элементов в
// массиве
//
// Для выполнения этого задания вам почти точно придётся реализовать обобщённую
// функцию обмена значениями. Попытайтесь сделать это как можно более эффективно
//
// Посылка должна состоять из функции selstep (допустимо также любое количество
// вспомогательных), и не должна содержать функцию main

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp_t)(void const *lhs, void const *rhs);

static int byteswap(void *const pa, void *const pb, int eltsize) {
	void *buf;
	if (memcmp(pa, pb, eltsize) == 0)
		return 0;
	if (!(buf = malloc(eltsize)))
		return -1;
	memcpy(buf, pa, eltsize);
	memcpy(pa, pb, eltsize);
	memcpy(pb, buf, eltsize);
	free(buf);
	return 0;
}

int selstep(void *parr, int eltsize, int numelts, int nsorted, cmp_t cmp) {
	int min_idx = nsorted;
	assert(nsorted < numelts);
	for (int i = nsorted + 1; i < numelts; ++i) {
		if (cmp((unsigned char *)parr + i * eltsize,
				(unsigned char *)parr + min_idx * eltsize)) {
			min_idx = i;
		}
	}
	return byteswap((unsigned char *)parr + nsorted * eltsize,
					(unsigned char *)parr + min_idx * eltsize, eltsize);
}

int main(void) { return 0; }
