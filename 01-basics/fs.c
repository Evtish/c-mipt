#include <stdio.h>

// 1. считаем факториал, пока не превзойдём число
// 2. множитель = число / факториал из предыдущей итерации
// 3. работаем с разностью аналогично
void fs(char *res, unsigned int a) { return; }

int main(void) {
	unsigned int a;
	if (scanf("%u", &a) != 1) {
		return 1;
	}
	char res[32];
	fs(res, a);
	printf("%s\n", res);
	return 0;
}
