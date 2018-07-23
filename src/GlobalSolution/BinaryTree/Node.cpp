#include "stdafx.h"
#include "Node.h"
#include <algorithm>

void Node::UpdateParentNodeDistances()
{
	int left = 0;
	int right = 0;

	if (this->Left != nullptr)
	{
		left = this->Left->DistanceFromLeaf + 1;
	}

	if (this->Right != nullptr)
	{
		right = this->Right->DistanceFromLeaf + 1;
	}

	this->DistanceFromLeaf = std::max(left, right);

	if (this->Parent != nullptr)
	{
		Parent->UpdateParentNodeDistances();
	}
}

Node::Node(int key, int value)
{
	Parent = Left = Right = nullptr;
	Key = key;
	Value = value;
	DistanceFromLeaf = 0;
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

int Node::GetKey()
{
	return this->Key;
}

int Node::GetValue()
{
	return this->Value;
}


