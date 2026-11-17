// Problem MM — минимум и максимум
//
// Ваша задача -- написать программу, которая:
//
// Считывает со стандартного ввода размер массива и дальше сам массив.
//
// Печатает на стандартный вывод минимальный и максимальный элементы.
//
// Если в массиве только один элемент, напечатайте его
//
// Если элементов нет, напечатайте "0 0"

#include <stddef.h>
#include <stdio.h>

int main(void) {
	size_t len, i;
	int n, min = 0, max = 0;
	if (scanf("%zu", &len) != 1)
		return 1;
	if (len <= 0) {
		puts("0 0");
		return 0;
	}
	for (i = 0; i < len; ++i) {
		if (scanf("%d", &n) != 1)
			return 1;
		if (i <= 0 || n < min)
			min = n;
		if (i <= 0 || n > max)
			max = n;
	}
	if (min == max)
		printf("%d\n", min);
	else
		printf("%d %d\n", min, max);
	return 0;
}
