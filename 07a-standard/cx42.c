#include <stdio.h>
int foo(int c) {
	int x, y;
	y = c ? x : 42; // при c == true операция y = x undefined поэтому проверка с
					// может не проводиться
	return y;
}
int main() { printf("%d\n", foo(1)); }
