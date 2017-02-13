#include <cstddef>
#include <stdexcept>

/*
 * min -- najnmiejsza liczba z tablicy
 * max -- najwieksza liczba z tablicy
 */
void bucket(int *array, size_t length, int min, int max)
{
	if (max < min)
		throw std::invalid_argument("max lower than min");
	size_t buckets_length, i, buck, amount;
	buckets_length = max - min + 1;
	int buckets[buckets_length];
	for (buck=0; buck < buckets_length; buck++)
		buckets[buck] = 0;
	for (i=0; i < length; i++)
		++buckets[array[i] - min];
	i = 0;
	for (buck=0; buck < buckets_length; buck++)
		for (amount=buckets[buck]; amount > 0; amount--)
			array[i++] = buck + min;
}
