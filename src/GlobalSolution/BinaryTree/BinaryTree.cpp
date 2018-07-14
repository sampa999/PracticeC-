#include "stdafx.h"
#include <new>
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

long BinaryTree::Insert(int key, int value)
{
	Node * node = new (std::nothrow) Node();

	if (node == nullptr)
	{
		return ERROR_OUTOFMEMORY;
	}

	node->Key = key;
	node->Value = value;

	if (head == nullptr)
	{
		head = node;
		return ERROR_SUCCESS;
	}

	Node * current = head;

	while (true)
	{
		if (key < current->Key)
		{
			if (current->Left == nullptr)
			{
				node->Parent = current;
				current->Left = node;
				return ERROR_SUCCESS;
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
				node->Parent = current;
				current->Right = node;
				return ERROR_SUCCESS;
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
			return ERROR_SUCCESS;
		}
	}
}

long BinaryTree::Find(int key, int & value)
{
	Node * current = head;

	while (current != nullptr)
	{
		if (current->Key == key)
		{
			value = current->Value;
			return ERROR_SUCCESS;
		}
		else if (current->Key > key)
		{
			current = current->Right;
		}
		else
		{
			current = current->Left;
		}
	}

	return ERROR_NOT_FOUND;
}
