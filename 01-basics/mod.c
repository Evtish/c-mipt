#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int eu_mod(int x, int y) {
	int r;
	assert(y != 0);
	r = x % y;
	if (r < 0)
		r += abs(y);
	return r;
}

int main(void) {
	printf("%d %% %d = %d\n", 26, 3, 26 % 3);
	printf("%d %% %d = %d\n", 3, 26, 3 % 26);
	printf("%d %% %d = %d\n", -26, 3, -26 % 3);
	printf("%d %% %d = %d\n", 3, -26, 3 % (-26));
	printf("%d %% %d = %d\n", 26, -3, 26 % (-3));
	printf("%d %% %d = %d\n", -3, 26, -3 % 26);
	printf("%d %% %d = %d\n", -26, -3, -26 % (-3));
	printf("%d %% %d = %d\n", -3, -26, -3 % (-26));

	printf("----------\n");

	printf("%d %% %d = %d\n", 26, 3, eu_mod(26, 3));
	printf("%d %% %d = %d\n", 3, 26, eu_mod(3, 26));
	printf("%d %% %d = %d\n", -26, 3, eu_mod(-26, 3));
	printf("%d %% %d = %d\n", 3, -26, eu_mod(3, (-26)));
	printf("%d %% %d = %d\n", 26, -3, eu_mod(26, (-3)));
	printf("%d %% %d = %d\n", -3, 26, eu_mod(-3, 26));
	printf("%d %% %d = %d\n", -26, -3, eu_mod(-26, (-3)));
	printf("%d %% %d = %d\n", -3, -26, eu_mod(-3, (-26)));

	return 0;
}
