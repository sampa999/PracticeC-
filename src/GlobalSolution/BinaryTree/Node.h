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

	~Node()
	{
		Value = 0;
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

	void UpdateDepthOfChildren()
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

		int newDepth = max(leftDepth, rightDepth);

		if (newDepth != this->DepthOfChildren)
		{
			this->DepthOfChildren = newDepth;
			if (Parent != nullptr)
			{
				Parent->UpdateDepthOfChildren();
			}
		}
	}

	Node * Parent;
	Node * Left;
	Node * Right;
	int Key;
	int Value;
	int DepthOfChildren; // 0 means no children
};