// Problem NS -- системы счисления
// Дано целое положительное (unsigned int) число x и основание системы счисления
// y Будем считать, что y > 1 и что y < 11 и что x > 0 Необходимо написать
// программу, которая печатает на стандартный вывод число x в системе счисления
// по основанию y Посылка должна состоять из программы, считывающей со
// стандартного ввода два числа: x в десятичной системе и основание новой
// системы y и выводящей на стандартный вывод без пробелов представление x по
// новому основанию знак за знаком

#include <math.h>
#include <stdio.h>

// Assuming base > 1 and base < 11 and n > 0
void from_dec(char *n_conv, size_t s, unsigned int n, unsigned int base) {
	n_conv[s - 1] = '\0';
	for (size_t i = s - 1; i > 0; i--) {
		n_conv[i - 1] = '0' + (n % base);
		n /= base;
	}
}

int main(void) {
	unsigned int n, base;
	if (scanf("%u%u", &n, &base) != 2)
		return 1;
	const size_t s = (size_t)(log(n) / log(base)) + 2;
	char n_conv[s];
	from_dec(n_conv, s, n, base);
	printf("%s\n", n_conv);
	return 0;
}
