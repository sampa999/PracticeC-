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
