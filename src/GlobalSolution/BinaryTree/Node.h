#pragma once

enum ChildType
{
	Root,
	Left,
	Right
};

class Node
{
	friend class BinaryTree;
public:
	Node(int key, int value);

	~Node();

	ChildType ChildType();

	void UpdateDepthOfChildren();
	Node * Rebalance();
	void EvaluateInOrder(void(*func)(Node *));
	void EvaluatePostOrder(void(*func)(Node *));
	void DeleteTree();
	Node * Delete();

	int get_Key() { return Key; }
	int get_Value() { return Value; }
	bool IsBalanced();
	Node * Left;
	Node * Right;
	int DepthOfChildren; // 0 means no children

private:
	Node * Parent;
	int Key;
	int Value;
};