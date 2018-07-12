#include "stdafx.h"
#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	head = nullptr;
}

void BinaryTree::Insert(int value)
{
	Node * node = new Node();
	node->Value = value;
	node->Left = node->Right = nullptr;

	if (head == nullptr)
	{
		head = node;
		return;
	}

	Node * current = head;
	while (true)
	{
		if (value < current->Value)
		{
			if (current->Left == nullptr)
			{
				current->Left = node;
				return;
			}
			else
			{
				current = current->Left;
			}
		}
		else
		{
			if (current->Right == nullptr)
			{
				current->Right = node;
				return;
			}
			else
			{
				current = current->Right;
			}
		}
	}
}