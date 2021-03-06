// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SingleLinkNode.h"

SingleLinkNode * CreateSingleLinkList(int length)
{
	SingleLinkNode * head = nullptr;

	for (int i = length; i > 0; i--)
	{
		SingleLinkNode * next = new SingleLinkNode();

		next->Value = i;
		next->Next = head;
		head = next;
	}

	return head;
}

void PrintSingleLinkList(SingleLinkNode * head)
{
	while (head != nullptr)
	{
		printf("%d ", head->Value);
		head = head->Next;
	}

	printf("\n");
}

SingleLinkNode * ReverseSingleLinkListRecurse(SingleLinkNode * head)
{
	if (head == nullptr || head->Next == nullptr)
	{
		return head;
	}

	SingleLinkNode * newHead = ReverseSingleLinkListRecurse(head->Next);

	head->Next->Next = head;

	head->Next = nullptr;

	return newHead;
}

SingleLinkNode * ReverseSingleLinkListNoRecurse(SingleLinkNode * head)
{
	if (head == nullptr || head->Next == nullptr)
	{
		return head;
	}

	SingleLinkNode * current = head;
	SingleLinkNode * next = nullptr;
	SingleLinkNode * prev = nullptr;

	while (true)
	{
		next = current->Next;
		current->Next = prev;
		if (next == nullptr)
		{
			return current;
		}
		else
		{
			prev = current;
			current = next;
			next = next->Next;
		}
	}
}

int main()
{
	SingleLinkNode * head = CreateSingleLinkList(20);
	PrintSingleLinkList(head);
	PrintSingleLinkList(ReverseSingleLinkListRecurse(head));
	head = CreateSingleLinkList(20);
	PrintSingleLinkList(head);
	PrintSingleLinkList(ReverseSingleLinkListNoRecurse(head));
	return 0;
}

