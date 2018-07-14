#pragma once

#include <windows.h>
#include "Node.h"

class BinaryTree
{
public:
	BinaryTree();

	long Insert(int key, int value);
	long Find(int key, int & value);
	void PrintInOrder();

private:
	Node * head;
	void PrintInOrder(Node * head);
};