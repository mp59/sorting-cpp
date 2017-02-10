#include <cstddef>
#define SWAP(a, b, tmp) (tmp = a, a = b, b = tmp)

void insert(int *array, size_t length)
{
	size_t i, current;
	int tmp;
	for (i=1; i < length; i++)
		for (current=i; current > 0 && array[current-1] > array[current]; current--)
			SWAP(array[current-1], array[current], tmp);
}
