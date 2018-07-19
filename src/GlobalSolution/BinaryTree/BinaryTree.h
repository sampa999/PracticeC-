#pragma once

#include <windows.h>
#include "Node.h"

class BinaryTree
{
public:
	BinaryTree();

	long Insert(int key, int value);
	long Insert(int key, int value, bool & updated);
	long Find(int key, int & value);
	long Delete(int key);
	void PrintInOrder();
	void EvaluateInOrder(void(*f)(Node *));

private:
	Node * head;
	void EvaluateInOrder(void(*f)(Node *), Node * current);
	Node * FindNode(int key);
	Node * InsertNodeToLeft(Node * head, Node * node);
};