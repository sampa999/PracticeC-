#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\BinaryTree\BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTree_Tests
{		
	Node * nodeArray[20];
	int nodeIndex;

	TEST_CLASS(Test1)
	{
	public:
		
		TEST_METHOD(InstantiateTree)
		{
			BinaryTree * tree = new (std::nothrow) BinaryTree();

			Assert::IsNotNull(tree);
		}

		TEST_METHOD(Insert)
		{
			BinaryTree * tree = new BinaryTree();

			long err = tree->Insert(0, 100);

			Assert::AreEqual(ERROR_SUCCESS, err);
		}

		static void EvalFunction(Node * node)
		{
			nodeArray[nodeIndex++] = node;
		}

		TEST_METHOD(EvaluateEmptyTree)
		{
			BinaryTree * tree = new BinaryTree();

			nodeIndex = 0;

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(0, nodeIndex);
		}

		TEST_METHOD(EvaluateOneElementTree)
		{
			BinaryTree * tree = new BinaryTree();

			nodeIndex = 0;

			tree->Insert(0, 100);

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(1, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->Key);
			Assert::AreEqual(100, nodeArray[0]->Value);
		}

		TEST_METHOD(EvaluateBalancedTree)
		{
			BinaryTree * tree = new BinaryTree();

			nodeIndex = 0;

			tree->Insert(10, 100);
			tree->Insert(9, 99);
			tree->Insert(11, 101);

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(3, nodeIndex);
			Assert::AreEqual(9, nodeArray[0]->Key);
			Assert::AreEqual(99, nodeArray[0]->Value);
			Assert::AreEqual(10, nodeArray[1]->Key);
			Assert::AreEqual(100, nodeArray[1]->Value);
			Assert::AreEqual(11, nodeArray[2]->Key);
			Assert::AreEqual(101, nodeArray[2]->Value);
		}

	};
}