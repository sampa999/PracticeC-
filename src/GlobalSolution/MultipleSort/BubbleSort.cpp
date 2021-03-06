#include "stdafx.h"
#include "BubbleSort.h"
#include "SortHelpers.h"

SortStatistics * BubbleSort::Sort(int * array, int size, bool verbose)
{
	SortStatistics * stats = new SortStatistics();

	bool sorted = false;

	printArray(array, size, verbose);

	while (!sorted)
	{
		sorted = true;

		for (int i = 0; i < size - 1; i++)
		{
			stats->Reads += 2; // read array[i] and array[i+1]
			if (array[i] > array[i + 1])
			{
				stats->Writes += 2; // Need to swap array[i] and array[i+1]
				int tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				sorted = false;
				printArray(array, size, verbose);
			}
		}
	}

	return stats;
}
