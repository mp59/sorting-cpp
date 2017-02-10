#include <cstddef>
#define SWAP(a, b, tmp) (tmp = a, a = b, b = tmp)

void bubble(int *array, size_t length)
{
	size_t i;
	int tmp;
	bool finished = false;
	while (!finished) {
		finished = true;
		for (i=0; i < length - 1; i++)
			if (array[i+1] < array[i]) {
				SWAP(array[i], array[i+1], tmp);
				finished = false;
			}
	}
}

void bubble_optimal(int *array, size_t length)
{
	size_t i, not_sorted_length;
	int tmp;
	while (length) {
		not_sorted_length = 0;
		for (i=0; i < length - 1; i++)
			if (array[i+1] < array[i]) {
				SWAP(array[i], array[i+1], tmp);
				not_sorted_length = i + 1;
			}
		length = not_sorted_length;
	}
}
