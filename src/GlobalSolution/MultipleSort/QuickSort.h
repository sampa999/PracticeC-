#pragma once

#include "stdafx.h"
#include "ISortInterface.h"
#include "SortHelpers.h"

class QuickSort : public ISortInterface
{
public:
	SortStatistics * Sort(int * array, int size, bool verbose);

private:
	void Sort(int * array, int size, int low, int high, bool verbose, SortStatistics * stats);
	int Partition(int * array, int size, int low, int high, bool verbose, SortStatistics * stats);
};

