#include <cstddef>
#define SWAP(a, b, tmp) (tmp = a, a = b, b = tmp)

size_t find_place(int *array, size_t start, size_t stop, int value)
{
	size_t middle;
	while (true) {
		if (start == stop)
			return start;
		middle = (start + stop - 1) / 2;
		if (array[middle] < value)
			start = middle + 1;
		else if (middle > start && array[middle-1] > value)
			stop = middle - 1;
		else
			return middle;
	}
}

void binary_insert(int *array, size_t length)
{
	size_t i, current_index, insert_index;
	int tmp;
	for (i=1; i < length; i++) {
		insert_index = find_place(array, 0, i, array[i]);
		for (current_index=i; current_index > insert_index; current_index--) {
			SWAP(array[current_index], array[current_index-1], tmp);
		}
	}
}
