// BinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryTree.h"
#include <time.h>
#include <random>

BinaryTree * GenerateBinaryTree(int size)
{
	BinaryTree * tree = new BinaryTree();

	for (int i = 0; i < size; i++)
	{
		tree->Insert(rand() % 100, rand() % 100);
	}

	return tree;
}

int main()
{
	srand((unsigned int)time(nullptr));

	BinaryTree * tree = GenerateBinaryTree(20);

	tree->PrintInOrder();

    return 0;
}

