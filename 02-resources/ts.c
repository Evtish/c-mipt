// Problem TS -- площадь треугольника
// Вам заранее задан тип данных треугольника
// Ваша задача написать функцию с заданным наперёд именем double_area, которая
// возвращает его удвоенную площадь

#ifdef CONTEST
#include "u_template.h"
#else
#include <stdio.h>

struct point_t {
	int x, y;
};

struct triangle_t {
	struct point_t pts[3];
};
#endif

int double_area(struct triangle_t tr) {
	int a, b, c, d, double_area;
	a = tr.pts[1].x - tr.pts[0].x;
	b = tr.pts[1].y - tr.pts[0].y;
	c = tr.pts[2].x - tr.pts[0].x;
	d = tr.pts[2].y - tr.pts[0].y;
	double_area = a * d - b * c;
	return double_area > 0 ? double_area : -double_area;
}

#ifndef CONTEST
int main(void) {
	struct triangle_t tr;
	int s = scanf("%d%d%d%d%d%d", &tr.pts[0].x, &tr.pts[0].y, &tr.pts[1].x,
				  &tr.pts[1].y, &tr.pts[2].x, &tr.pts[2].y);
	if (s != 6)
		return 1;
	printf("%d\n", double_area(tr));
	return 0;
}
#endif
