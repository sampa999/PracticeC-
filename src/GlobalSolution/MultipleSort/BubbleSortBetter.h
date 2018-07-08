#pragma once

#include "ISortInterface.h"

class BubbleSortBetter : public SortInterface
{
public:
	virtual SortStatistics * Sort(int * array, int size, bool verbose);
};
