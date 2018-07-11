#pragma once

#include "ISortInterface.h"

class BubbleSortBetter : public ISortInterface
{
public:
	SortStatistics * Sort(int * array, int size, bool verbose);
};
