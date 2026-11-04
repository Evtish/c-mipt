// Problem BP -- старший и младший бит
// Вам предлагается найти позицию старшего и младшего установленных битов в
// числе. Посылка должна состоять из программы, считывающей со стандартного
// ввода число N и выводящей на стандартный вывод номер его старшего и младшего
// бита. В случае если установленных битов в числе нет, вы должны выдать строчку
// "NO".

#include <assert.h>
#include <limits.h>
#include <stdio.h>

int msb(unsigned int n) {
	unsigned int bits = (sizeof n) * CHAR_BIT, mask = 1u << (bits - 1);
	int i = bits - 1;
	if (n == 0)
		return -1;
	while (!(n & mask)) {
		i--;
		n <<= 1;
	}
	assert(i >= 0);
	return i;
}

int lsb(unsigned int n) {
	int i = 0;
	if (n == 0)
		return -1;
	while (!(n & 1u)) {
		i++;
		n >>= 1;
	}
	assert(i >= 0);
	return i;
}

int main(void) {
	unsigned int n;
	int m, l;
	if (scanf("%u", &n) != 1) {
		fprintf(stderr, "Invalid input. Input one non-negative integer\n");
		return 1;
	}
	m = msb(n);
	l = lsb(n);
	if (m == -1 && l == -1)
		printf("NO\n");
	else
		printf("%d %d\n", m, l);
	return 0;
}
