#include "stdafx.h"
#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	head = nullptr;
}

void BinaryTree::PrintInOrder()
{
	PrintInOrder(head);
	printf("\n");
}

void BinaryTree::PrintInOrder(Node * current)
{
	if (current == nullptr)
	{
		return;
	}

	PrintInOrder(current->Left);
	printf("%d-%d ", current->Key, current->Value);
	PrintInOrder(current->Right);
}

void BinaryTree::Insert(int key, int value)
{
	Node * node = new Node();
	node->Key = key;
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
		if (key < current->Key)
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
		else if (key > current->Key)
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
		else
		{
			// Update case
			current->Value = value;
			return;
		}
	}
}