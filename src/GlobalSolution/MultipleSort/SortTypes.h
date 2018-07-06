#pragma once

struct SortStatistics
{
	int Reads; // This is the number of reads done during the sort operation
	int Writes; // This is the number of writes done during the sort operation
};

class SortInterface
{
public:
	virtual SortStatistics * Sort(int * array, int size) = 0;
};

class BubbleSort : public SortInterface
{
public:
	virtual SortStatistics * Sort(int * array, int size);
private:
};
