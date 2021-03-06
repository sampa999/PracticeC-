// MultipleSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <time.h>
#include "BubbleSort.h"
#include "BubbleSortBetter.h"
#include "QuickSort.h"

int * randomArray(int size)
{
	int * dataArray = new int[size];
	srand((unsigned int)time(NULL));

	for (int i = 0; i<size; i++)
	{
		dataArray[i] = rand() % (size * 100);
	}

	return dataArray;
}

int * copyArray(int * array, int size)
{
	int * dataArray = new int[size];

	for (int i = 0; i < size; i++)
	{
		dataArray[i] = array[i];
	}

	return dataArray;
}

int main()
{
	const int arraySize = 20000;

	int * ptrDataArray = randomArray(arraySize);
	BubbleSort * bubbleSort = new BubbleSort();

	SortStatistics * stats = bubbleSort->Sort(copyArray(ptrDataArray, arraySize), arraySize, false);
	printf("BubbleSort %d Reads, %d Writes\n", stats->Reads, stats->Writes);

	BubbleSortBetter * bubbleSortBetter = new BubbleSortBetter();

	stats = bubbleSortBetter->Sort(copyArray(ptrDataArray, arraySize), arraySize, false);
	printf("BubbleSortBetter %d Reads, %d Writes\n", stats->Reads, stats->Writes);

	QuickSort * quickSort = new QuickSort();

	stats = quickSort->Sort(copyArray(ptrDataArray, arraySize), arraySize, false);
	printf("QuickSort %d Reads, %d Writes\n", stats->Reads, stats->Writes);

	return 1;
}
