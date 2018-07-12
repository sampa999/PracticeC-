#pragma once

#include "Node.h"

class BinaryTree
{
public:
	BinaryTree();

	void Insert(int value);

private:
	Node * head;
};