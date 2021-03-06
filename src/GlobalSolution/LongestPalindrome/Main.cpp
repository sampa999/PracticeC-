// LongestPalindrome.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <utility>

void Usage()
{
	printf("LongestPalindrom.exe <string>\n");
}

bool IsPalindrome(char * string, int start, int end)
{
	while (start <= end)
	{
		if (string[start] != string[end])
		{
			return false;
		}
		start++;
		end--;
	}

	return true;
}

std::pair<int, int> * FindLongestPalindrome(char * string)
{
	if (string == nullptr)
	{
		return nullptr;
	}

	int length = (int) strlen(string);
	int testLength = length;

	while (testLength >= 0)
	{
		int maxOffset = length - testLength;

		for (int offset = 0; offset <= maxOffset; offset++)
		{
			if (IsPalindrome(string, offset, offset + testLength))
			{
				return new std::pair<int, int>(offset, offset + testLength);
			}
		}

		testLength--;
	}

	// Should never reach here.
	return nullptr;
}

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		Usage();
		return 1;
	}

	std::pair<int, int> * result = FindLongestPalindrome(argv[1]);

	if (result == nullptr)
	{
		printf("Internal error\n");
	}
	else
	{
		for (int i = result->first; i <= result->second; i++)
		{
			printf("%c", argv[1][i]);
		}
		printf("\n");
	}

    return 0;
}

