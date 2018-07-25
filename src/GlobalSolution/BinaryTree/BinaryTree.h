#pragma once

#include <windows.h>
#include "Node.h"

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	long Insert(int key, int value);
	long Insert(int key, int value, bool & updated);
	long Find(int key, int & value);
	long Delete(int key);
	void EvaluateInOrder(void(*f)(Node *));
	void UpdateDepthOfChildren();
	void Rebalance();

private:
	Node * Head;
	Node * FindNode(int key);
	Node * InsertNodeToLeft(Node * head, Node * node);
};