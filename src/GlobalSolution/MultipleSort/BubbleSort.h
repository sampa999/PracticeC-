#pragma once

#include "ISortInterface.h"

class BubbleSort : public ISortInterface
{
public:
	SortStatistics * Sort(int * array, int size, bool verbose);
};

