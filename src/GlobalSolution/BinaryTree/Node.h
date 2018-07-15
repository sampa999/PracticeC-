#pragma once

struct Node
{
	Node(int key, int value)
	{
		Parent = Left = Right = nullptr;
		Key = key;
		Value = value;
	}

	Node * Parent;
	Node * Left;
	Node * Right;
	int Key;
	int Value;
};