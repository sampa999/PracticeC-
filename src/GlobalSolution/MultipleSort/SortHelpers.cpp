#include "stdafx.h"
#include "SortHelpers.h"

void printArray(int * array, int size, bool verbose)
{
	if (!verbose)
	{
		return;
	}

	for (int i = 0; i < size; i++)
	{
		printf("%2d ", array[i]);
	}

	printf("\n");
}

