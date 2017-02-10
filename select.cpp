#include <cstddef>
#define SWAP(a, b, tmp) (tmp = a, a = b, b = tmp)

void select(int *array, size_t length)
{
	size_t current, to_swap, i;
	int tmp;
	for (current=0; current < length; current++) {
		to_swap = current;
		for (i=current+1; i < length; i++) {
			if (array[i] < array[to_swap])
				to_swap = i;
		}
		if (to_swap != current)
			SWAP(array[current], array[to_swap], tmp);
	}
}
