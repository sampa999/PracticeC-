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
	void EvaluateInOrder(void(*f)(Node *));

private:
	Node * head;
	void EvaluateInOrder(void(*f)(Node *), Node * current);
};