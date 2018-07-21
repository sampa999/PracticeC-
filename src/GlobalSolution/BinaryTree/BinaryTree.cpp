#include "stdafx.h"
#include <new>
#include "BinaryTree.h"
#include <memory>

BinaryTree::BinaryTree()
{
	Head = nullptr;
}

BinaryTree::~BinaryTree()
{
	DeleteTree(Head);
}

void PrintFunc(Node * node)
{
	printf("%d-%d ", node->Key, node->Value);
}

void BinaryTree::PrintInOrder()
{
	EvaluateInOrder(PrintFunc, Head);
	printf("\n");
}

void BinaryTree::EvaluateInOrder(void(*func)(Node *))
{
	EvaluateInOrder(func, Head);
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
	Node * current = Head;

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

/*
	Inserts the given node below the left most node of head.
*/
Node * BinaryTree::InsertNodeToLeft(Node * head, Node * node)
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

void BinaryTree::DeleteTree(Node * node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->Left != nullptr)
	{
		DeleteTree(node->Left);
		node->Left = nullptr;
	}

	if (node->Right != nullptr)
	{
		DeleteTree(node->Right);
		node->Right = nullptr;
	}

	node->Parent = nullptr;
	delete node;
}

long BinaryTree::Insert(int key, int value)
{
	bool updated;

	return Insert(key, value, updated);
}

long BinaryTree::Insert(int key, int value, bool & updated)
{
	Node * node = new (std::nothrow) Node(key, value);

	updated = false;

	if (node == nullptr)
	{
		return ERROR_OUTOFMEMORY;
	}

	if (Head == nullptr)
	{
		Head = node;
		return ERROR_SUCCESS;
	}

	Node * current = Head;

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
			delete node;
			updated = true;
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

/*
	Find the node with the given key
	Take the nodes left branch, and move it to the left of the nodes right branch.
	Set the nodes right branch parent to the nodes parent
	Set the nodes parents child to the node
	Example:
		Remove 7 below by setting 8->left to 6 and 6->parent to 8 and setting 8->parent to 5 and 5->right to 8
		Then 7 can be safely deleted since no one references it

	        5
		 3     7
	   1      6 8
	    2

		    5
	     3     8
	   1      6
	    2
*/
long BinaryTree::Delete(int key)
{
	std::unique_ptr<Node> node(FindNode(key));

	if (node == nullptr)
	{
		return ERROR_NOT_FOUND;
	}

	// Move the left node to the left of the right node.
	// This maintains order in the tree when the node is removed.
	node->Right = InsertNodeToLeft(node->Right, node->Left);

	switch (node->ChildType())
	{
	case ChildType::Root:
	{
		Head = node->Right;
		if (Head != nullptr)
		{
			Head->Parent = nullptr;
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
		if (node->Right != nullptr)
		{
			node->Right->Parent = node->Parent;
		}
	}
	}

	return ERROR_SUCCESS;
}
