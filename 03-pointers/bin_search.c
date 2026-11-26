#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define LEN 10

size_t bin_search(const int *const arr, size_t len, int key) {
	size_t left, right;
	assert(len > 0);
	left = 0, right = len - 1;
	while (left <= right) {
		size_t mid;
		// To prevent mid - 1 overflowing when mid == 0
		if (left == right && arr[left] != key)
			break;
		mid = left + (right - left) / 2;
		if (arr[mid] > key) {
			assert(mid > 0);
			right = mid - 1;
		} else if (arr[mid] < key) {
			assert(mid < SIZE_MAX);
			left = mid + 1;
		} else {
			return mid;
		}
	}
	return len;
}

int main(void) {
	int arr[LEN] = {-2, 0, 1, 3, 4, 5, 8, 10, 1000, 1001}, key;
	size_t found_pos;
	if (scanf("%d", &key) != 1) {
		fputs("Invalid key. Input one integer\n", stderr);
		return 1;
	}
	found_pos = bin_search(arr, LEN, key);
	if (found_pos >= LEN) {
		fputs("Key not found\n", stderr);
		return 1;
	}
	assert(arr[found_pos] == key);
	printf("arr[%zu] == %d\n", found_pos, arr[found_pos]);
	return 0;
}
