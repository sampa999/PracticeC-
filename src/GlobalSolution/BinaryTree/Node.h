#pragma once

enum ChildType
{
	Root,
	Left,
	Right
};

struct Node
{
	Node(int key, int value)
	{
		Parent = Left = Right = nullptr;
		Key = key;
		Value = value;
		DepthOfChildren = 0;
	}

	ChildType ChildType()
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

	Node * Parent;
	Node * Left;
	Node * Right;
	int Key;
	int Value;
	int DepthOfChildren; // 0 means no children
};