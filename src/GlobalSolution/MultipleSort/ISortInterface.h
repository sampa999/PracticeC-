#pragma once

#include "SortStatistics.h"

class ISortInterface
{
public:
	virtual SortStatistics * Sort(int * array, int size, bool verbose) = 0;
};