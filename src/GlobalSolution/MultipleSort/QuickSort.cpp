#include "stdafx.h"
#include "QuickSort.h"
#include "SortHelpers.h"

SortStatistics * QuickSort::Sort(int * array, int size, bool verbose)
{
	SortStatistics * stats = new SortStatistics();

	Sort(array, size, 0, size, verbose, stats);

	return stats;
}

void QuickSort::Sort(int * array, int size, int low, int high, bool verbose, SortStatistics * stats)
{
	if (low >= high)
	{
		return;
	}

	printArray(array, size, verbose);
	int p = Partition(array, size, low, high, verbose, stats);
	Sort(array, size , low, p, verbose, stats);
	Sort(array, size, p + 1, high, verbose, stats);
}

int QuickSort::Partition(int * array, int size, int low, int high, bool verbose, SortStatistics * stats)
{
	int pivotIndex = high - 1;
	int pivot = array[pivotIndex];
	int checkIndex = low;

	while (checkIndex < pivotIndex)
	{
		if (array[checkIndex] > pivot)
		{
			printArray(array, size, verbose);
			array[pivotIndex] = array[checkIndex];
			array[checkIndex] = array[pivotIndex-1];
			array[pivotIndex-1] = pivot;
			pivotIndex--;
		}
		else
		{
			checkIndex++;
		}
	}

	return pivotIndex;
}
