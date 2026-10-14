#include <stdio.h>

void continued_fraction(int a, int b) {
	while (b != 0) {
		printf("%d ", a / b);
		int tmp = a;
		a = b;
		b = tmp % b;
	}
}

int main(void) {
	int a, b;
	if (scanf("%d%d", &a, &b) != 2 || b == 0)
		return 1;
	continued_fraction(a, b);
	return 0;
}
