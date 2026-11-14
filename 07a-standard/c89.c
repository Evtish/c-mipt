#include <stdio.h>

static x; /* → static int x; */

main(void) {				   /* → int main(void) { */
	auto i;					   /* → auto int i; */
	for (i = 0; i < 5; i += 2) /* can not: for(int i = 0 ....) */
		x += i;
	printf("%d\n", x);
	return 0; /* mandatory in C90 */
}
