#include "stdafx.h"
#include "BubbleSortBetter.h"
#include "SortHelpers.h"

SortStatistics * BubbleSortBetter::Sort(int * array, int size, bool verbose)
{
	SortStatistics * stats = new SortStatistics();

	bool sorted = false;
	int unsortedIndex = size - 1;

	printArray(array, size, verbose);

	while (!sorted)
	{
		sorted = true;

		for (int i = 0; i < unsortedIndex; i++)
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

		unsortedIndex--;
	}

	return stats;
}
