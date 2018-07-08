#pragma once

#include "ISortInterface.h"

class BubbleSort : public SortInterface
{
public:
	virtual SortStatistics * Sort(int * array, int size, bool verbose);
private:

};

