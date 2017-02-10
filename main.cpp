#include <iostream>
#include "main.h"

void random_fill(int *, size_t, int);

int	main()
{
	size_t length, i;
	length = 6;
	int arr[length];
	random_fill(arr, length, 100);

	binary_insert(arr, length);
	for (i=0; i < length; i++)
		std::cout << arr[i] << std::endl;
	return 0;
}

void random_fill(int *arr, size_t length, int max_number)
{
	srand(time(NULL));
	for (size_t i=0; i < length; i++)
		arr[i] = rand() % max_number;
}
