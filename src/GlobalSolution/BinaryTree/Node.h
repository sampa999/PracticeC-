#pragma once

struct Node
{
	Node()
	{
		Parent = Left = Right = nullptr;
		Key = Value = 0;
	}

	Node * Parent;
	Node * Left;
	Node * Right;
	int Key;
	int Value;
};