#include <cstddef>

void merge_sort(int *, size_t);
void actual_merge_sort(int *, int *, size_t, size_t);
void merge(int *, int *, size_t, size_t, size_t);

void merge_sort(int *array, size_t length)
{
	int tmp[length];
	actual_merge_sort(array, tmp, 0, length);
}

void actual_merge_sort(int *array, int *tmp, size_t start, size_t stop)
{
	size_t center;
	if (stop > start+1) {  // more than one
		center = (stop + start) / 2;
		actual_merge_sort(array, tmp, start, center);
		actual_merge_sort(array, tmp, center, stop);
		merge(array, tmp, start, stop, center);
	}
}

void merge(int *array, int *tmp, size_t start, size_t stop, size_t center)
{
	size_t i, left_index, right_index;
	left_index = start;
	right_index = center;
	for (i=start; i < stop; i++) {
		if (right_index == stop)   // right array empty
			tmp[i] = array[left_index++];
		else if (left_index == center)   // left array empty
			tmp[i] = array[right_index++];
		else {
			if (array[left_index] < array[right_index])
				tmp[i] = array[left_index++];
			else
				tmp[i] = array[right_index++];
		}
	}
	for (i=start; i < stop; i++)
		array[i] = tmp[i];
}
