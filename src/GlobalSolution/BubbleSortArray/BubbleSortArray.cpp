// BubbleSortArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>

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

void printArray(int * array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%2d ", array[i]);
	}

	printf("\n");
}

void swap(int * array, int size, int i, int j)
{
	int tmpInt = array[i];
	array[i] = array[j];
	array[j] = tmpInt;
	printArray(array, size);
}

void sortStep(int * array, int size)
{
	for (int i = 0; i < size-1; i++)
	{
		if (array[i] > array[i + 1])
		{
			swap(array, size, i, i + 1);
		}
	}
}

void bubbleSort(int * array, int size)
{
	printArray(array, size);
	while (!isSorted(array, size))
	{
		sortStep(array, size);
	}
}

int * randomArray(int size)
{
	int * dataArray = new int[size];
	srand(time_t(NULL));

	for (int i = 0; i<size; i++)
	{
		dataArray[i] = rand() % (size * 100);
	}

	return dataArray;
}

int main()
{
	const int arraySize = 20;
	
	int * ptrDataArray = randomArray(arraySize);

	bubbleSort(ptrDataArray, arraySize);

    return 0;
}