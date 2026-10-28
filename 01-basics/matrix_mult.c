#include <stdio.h>

#define M 2
#define N 2

// res[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0]
// res[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1]
// res[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0]
// res[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1]
void matrix_mult(int res[M][M], int a[M][N], int b[N][M]) {
	for (int i = 0; i < M; i++) {
		int elem = 0;
		for (int j = 0; j < N; j++) {
			printf("%d %d\n", i, j);
			elem += a[i][j] * b[j][i];
		}
		res[i][i] = elem;
	}
}

int main(void) {
	int a[M][N];
	int b[N][M];
	for (int i = 0; i < 2 * M * N; i++) {
		int s;
		if (i < M * N)
			s = scanf("%d", &a[i / N][i % N]);
		else
			s = scanf("%d", &b[i / M][i % M]);
		if (s != 1) {
			fprintf(stderr, "Invalid input. Input %d integers\n", 2 * M * N);
			return 1;
		}
	}
	int res[M][M];
	matrix_mult(res, a, b);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d\t", res[i][j]);
		}
		fputc('\n', stdout);
	}
	return 0;
}
