#pragma once

#include "SortStatistics.h"

class SortInterface
{
public:
	virtual SortStatistics * Sort(int * array, int size, bool verbose) = 0;
};