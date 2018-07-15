#include "stdafx.h"
#include <new>
#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	head = nullptr;
}

void PrintFunc(Node * node)
{
	printf("%d-%d ", node->Key, node->Value);
}

void BinaryTree::PrintInOrder()
{
	EvaluateInOrder(PrintFunc, head);
	printf("\n");
}

void BinaryTree::EvaluateInOrder(void(*func)(Node *))
{
	EvaluateInOrder(func, head);
}

void BinaryTree::EvaluateInOrder(void(*func)(Node *), Node * current)
{
	if (current == nullptr)
	{
		return;
	}

	EvaluateInOrder(func, current->Left);
	func(current);
	EvaluateInOrder(func, current->Right);
}

long BinaryTree::Insert(int key, int value)
{
	Node * node = new (std::nothrow) Node(key, value);

	if (node == nullptr)
	{
		return ERROR_OUTOFMEMORY;
	}

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
