// Problem SCB — обобщённый бинарный поиск
//
// Бинарный поиск можно осуществлять в массиве произвольных элементов, обладая
// только информацией о размере элемента и функцией-компаратором. В этом задании
// считайте тип компаратора заданным заранее
//
// typedef int (*cmp_t)(const void *lhs, const void *rhs);
//
// Компаратор возвращает отрицательное число, если lhs логически меньше, чем
// rhs, 0 если они равны и положительное число, если lhs логически больше, чем
// rhs
//
// Ваша задача — написать функцию обобщённого бинарного поиска с заранее
// заданной сигнатурой
//
// void *cbsearch(const void *key, const void *base, int num, int size, cmp_t
// cmp);
//
// Здесь key это элемент, который ищется, base это массив в котором
// осуществляется поиск, size это размер элементов массива (и, соответственно,
// элемента key), num это количество элементов в массиве
//
// Решение более чем с логарифмической сложностью вряд ли уложится в лимит по
// времени
//
// Посылка должна состоять из функции cbsearch (допустимо также любое количество
// вспомогательных), и не должна содержать функцию main
//
// Функция cbsearch должна возвращать указатель на найденный элемент. Если
// ничего не найдено то можно вернуть нулевой указатель или указатель за концом
// массива

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define LEN 10

typedef int (*cmp_t)(const void *lhs, const void *rhs);

struct vec3_t {
	double x, y, z;
};

void *cbsearch(const void *key, const void *base, int num, int size,
			   cmp_t cmp) {
	ptrdiff_t left, right;
	assert(num > 0);
	assert(size > 0);
	left = 0, right = (num - 1) * size;
	while (left <= right) {
		ptrdiff_t mid = left + (right - left) / size / 2 * size;
		int cmpres = cmp((unsigned char *)base + mid, key);
		if (cmpres > 0)
			right = mid - size;
		else if (cmpres < 0)
			left = mid + size;
		else
			return (void *)((unsigned char *)base + mid);
	}
	return NULL;
}

static double vec3_len2(const struct vec3_t *const a) {
	return a->x * a->x + a->y * a->y + a->z * a->z;
}

static int cmp_vec3(const void *lhs, const void *rhs) {
	struct vec3_t *a = (struct vec3_t *)lhs, *b = (struct vec3_t *)rhs;
	double a_len2 = vec3_len2(a), b_len2 = vec3_len2(b);
	if (a_len2 > b_len2)
		return 1;
	else if (a_len2 < b_len2)
		return -1;
	return 0;
}

int main(void) {
	struct vec3_t base[LEN] = {{0, 0, 0},		{0.01, 0.02, 0.03},
							   {0.1, 0.1, 0.1}, {1, 1, 0.5},
							   {0.5, 1, 1},		{1, 0.5, 1},
							   {1, 1, 1},		{2, 1, 1},
							   {10, 10, 10},	{10, 10.1, 10}},
				  key;
	void *found_addr;
	size_t found_pos;
	if (scanf("%lf%lf%lf", &(key.x), &(key.y), &(key.z)) != 3) {
		fputs("Invalid key. Input thee rational numbers\n", stderr);
		return 1;
	}
	found_addr = cbsearch(&key, base, LEN, sizeof(*base), cmp_vec3);
	if (!found_addr) {
		fputs("Key not found\n", stderr);
		return 1;
	}
	found_pos =
		((unsigned char *)found_addr - (unsigned char *)base) / sizeof(*base);
	assert(vec3_len2(&base[found_pos]) == vec3_len2(&key));
	printf("base[%zu] == {%lf, %lf, %lf}\n", found_pos, base[found_pos].x,
		   base[found_pos].y, base[found_pos].z);
	return 0;
}
