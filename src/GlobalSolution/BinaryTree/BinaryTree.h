#pragma once

#include "Node.h"

class BinaryTree
{
public:
	BinaryTree();

	void Insert(int key, int value);
	void PrintInOrder();

private:
	Node * head;
	void PrintInOrder(Node * head);
};