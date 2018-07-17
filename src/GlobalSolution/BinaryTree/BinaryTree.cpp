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

Node * BinaryTree::FindNode(int key)
{
	Node * current = head;

	while (current != nullptr)
	{
		if (current->Key == key)
		{
			return current;
		}
		else if (current->Key > key)
		{
			current = current->Left;
		}
		else
		{
			current = current->Right;
		}
	}

	return nullptr;
}

Node * BinaryTree::InsertNode(Node * head, Node * node)
{
	if (head == nullptr)
	{
		return node;
	}

	if (node == nullptr)
	{
		return head;
	}

	while (head->Left != nullptr)
	{
		head = head->Left;
	}

	head->Left = node;
	node->Parent = head;

	return head;
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
	Node * node = FindNode(key);

	if (node != nullptr)
	{
		value = node->Value;
		return ERROR_SUCCESS;
	}

	return ERROR_NOT_FOUND;
}

long BinaryTree::Delete(int key)
{
	Node * node = FindNode(key);

	if (node == nullptr)
	{
		return ERROR_NOT_FOUND;
	}

	node->Right = InsertNode(node->Right, node->Left);

	switch (node->ChildType())
	{
	case ChildType::Root:
	{
		head = node->Right;
		if (head != nullptr)
		{
			head->Parent = nullptr;
		}
		break;
	}

	case ChildType::Left:
	{
		node->Parent->Left = node->Right;
		if (node->Right != nullptr)
		{
			node->Right->Parent = node->Parent;
		}
		break;
	}

	case ChildType::Right:
	{
		node->Parent->Right = node->Right;
		if (node->Right->Parent != nullptr)
		{
			node->Right->Parent = node->Parent;
		}
	}
	}

	return ERROR_SUCCESS;
}
