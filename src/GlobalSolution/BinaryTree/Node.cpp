#include "stdafx.h"
#include "Node.h"
#include <algorithm>

Node::Node(int key, int value)
{
	Parent = Left = Right = nullptr;
	Key = key;
	Value = value;
	DepthOfChildren = 0;
}

Node::~Node()
{
	Value = 0;
}

ChildType Node::ChildType()
{
	if (Parent == nullptr)
	{
		return ChildType::Root;
	}

	if (Parent->Right == this)
	{
		return ChildType::Right;
	}

	return ChildType::Left;
}

void Node::UpdateDepthOfChildren()
{
	int leftDepth = 0;
	int rightDepth = 0;

	if (Left != nullptr)
	{
		leftDepth = Left->DepthOfChildren + 1;
	}

	if (Right != nullptr)
	{
		rightDepth = Right->DepthOfChildren + 1;
	}

	int newDepth = std::max(leftDepth, rightDepth);

	if (newDepth != this->DepthOfChildren)
	{
		this->DepthOfChildren = newDepth;

		if (Parent != nullptr)
		{
			Parent->UpdateDepthOfChildren();
		}
	}
}

void Node::EvaluateInOrder(void(*func)(Node *))
{
	if (this == nullptr)
	{
		return;
	}

	Left->EvaluateInOrder(func);

	func(this);

	Right->EvaluateInOrder(func);
}

void Node::DeleteTree()
{
	if (Left != nullptr)
	{
		Left->DeleteTree();
		Left = nullptr;
	}

	if (Right != nullptr)
	{
		Right->DeleteTree();
		Right = nullptr;
	}

	Parent = nullptr;
	delete this;
}

// Delete self from the tree
Node * Node::Delete()
{
	Node * newRoot = Right;

	// Move Left branch to left most node of Right branch

	if (Right == nullptr)
	{
		newRoot = Left;
	}
	else
	{
		Node * current = Right;

		while (current->Left != nullptr)
		{
			current = current->Left;
		}

		current->Left = Left;
		if (Left != nullptr)
		{
			Left->Parent = current;
		}
	}

	if (newRoot != nullptr)
	{
		newRoot->Parent = Parent;
	}

	if (Parent != nullptr)
	{
		if (Parent->Left == this)
		{
			Parent->Left = newRoot;
		}
		else
		{
			Parent->Right = newRoot;
		}

		Parent->UpdateDepthOfChildren();
	}

	Parent = Left = Right = nullptr; // For safety

	delete this;

	return newRoot;
}

/*
This rebalances this nodes left and right trees.
This may result in this node no longer being at the root of it's own tree, thus the return value of Node *

Example: Rebalance 7
                    7
              3           B
          1      5
         0

Intermediate:
              3
          1       5
         0          7
                     B

Result:
              3
          1      7
         0      5 B

*/
Node * Node::Rebalance()
{
	int leftDepth = 0;
	int rightDepth = 0;

	if (Left != nullptr)
	{
		leftDepth = Left->DepthOfChildren;
	}

	if (Right != nullptr)
	{
		rightDepth = Right->DepthOfChildren;
	}

	if (leftDepth > rightDepth + 1)
	{
		Node * newRoot = this->Left;
		this->Left = nullptr;

		Node * current = newRoot;

		while (current->Right != nullptr)
		{
			current = current->Right;
		}

		current->Right = this;
		this->Parent = current;
		current->UpdateDepthOfChildren();
		
		Node * parent = current->Parent;
		parent->Right = current->Rebalance();
		return newRoot;
	}
	else if (rightDepth > leftDepth + 1)
	{
		Node * newRoot = this->Right;
		Node * current = newRoot;

		while (current->Left != nullptr)
		{
			current = current->Left;
		}

		current->Left = this;
		this->Parent = current;
		current->UpdateDepthOfChildren();

		Node * parent = current->Parent;
		parent->Left = current->Rebalance();
		return newRoot;
	}
}
