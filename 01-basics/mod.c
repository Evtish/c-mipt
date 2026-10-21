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
	printf("%d %% %d = %d\n", 26, 1, 26 % 1);
	printf("%d %% %d = %d\n", 1, 26, 1 % 26);
	printf("%d %% %d = %d\n", -26, 1, -26 % 1);
	printf("%d %% %d = %d\n", 1, -26, 1 % (-26));
	printf("%d %% %d = %d\n", 26, -1, 26 % (-1));
	printf("%d %% %d = %d\n", -1, 26, -1 % 26);
	printf("%d %% %d = %d\n", -26, -1, -26 % (-1));
	printf("%d %% %d = %d\n", -1, -26, -1 % (-26));

	printf("----------\n");

	printf("%d %% %d = %d\n", 26, 1, eu_mod(26, 1));
	printf("%d %% %d = %d\n", 1, 26, eu_mod(1, 26));
	printf("%d %% %d = %d\n", -26, 1, eu_mod(-26, 1));
	printf("%d %% %d = %d\n", 1, -26, eu_mod(1, (-26)));
	printf("%d %% %d = %d\n", 26, -1, eu_mod(26, (-1)));
	printf("%d %% %d = %d\n", -1, 26, eu_mod(-1, 26));
	printf("%d %% %d = %d\n", -26, -1, eu_mod(-26, (-1)));
	printf("%d %% %d = %d\n", -1, -26, eu_mod(-1, (-26)));

	return 0;
}
