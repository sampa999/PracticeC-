// BubbleSortArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool isSorted(int * array, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (array[i] > array[i + 1])
		{
			return false;
		}
	}

	return true;
}

void sortStep(int * array, int size)
{
	for (int i = 0; i < size-1; i++)
	{
		if (array[i] > array[i + 1])
		{
			int tmpInt = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmpInt;
		}
	}
}

void printArray(int * array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%2d ", array[i]);
	}

	printf("\n");
}

void sort(int * array, int size)
{
	printArray(array, size);
	while (!isSorted(array, size))
	{
		sortStep(array, size);
		printArray(array, size);
	}
}

int main()
{
	const int arraySize = 20;
	int * ptrDataArray = new int[arraySize];
	for (int i=0; i<arraySize; i++)
	{
		ptrDataArray[i] = arraySize - i;
	}

	sort(ptrDataArray, arraySize);

    return 0;
}

