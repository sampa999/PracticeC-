#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\BinaryTree\BinaryTree.h"
#include <random>
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTree_Tests
{		
	const int MaxNodes = 10000;
	Node * nodeArray[10000];
	int nodeIndex;

	TEST_CLASS(Test1)
	{
	public:
		
		TEST_METHOD(InstantiateTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());
		}

		TEST_METHOD(Insert)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			long err = tree->Insert(0, 100);

			Assert::AreEqual(ERROR_SUCCESS, err);
		}

		static void EvalFunction(Node * node)
		{
			nodeArray[nodeIndex++] = node;
		}

		TEST_METHOD(EvaluateEmptyTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			nodeIndex = 0;

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(0, nodeIndex);
		}

		TEST_METHOD(EvaluateOneElementTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			nodeIndex = 0;

			tree->Insert(0, 100);

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(1, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->Key);
			Assert::AreEqual(100, nodeArray[0]->Value);
		}

		TEST_METHOD(EvaluateBalancedTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

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

		TEST_METHOD(DeleteFromEmptyTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			long returnValue = tree->Delete(3);

			Assert::AreEqual(ERROR_NOT_FOUND, returnValue);
		}

		TEST_METHOD(DeleteFromOneElementTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			nodeIndex = 0;

			tree->Insert(2, 200);
			tree->EvaluateInOrder(&EvalFunction);

			long returnValue = tree->Delete(3);

			Assert::AreEqual(1, nodeIndex);
			Assert::AreEqual(ERROR_NOT_FOUND, returnValue);

			returnValue = tree->Delete(2);
			Assert::AreEqual(ERROR_SUCCESS, returnValue);

			nodeIndex = 0;
			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(0, nodeIndex);
		}

		TEST_METHOD(DeleteLeafFromTwoElementTreeLeftWeighted)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			tree->Insert(2, 200);
			tree->Insert(1, 100);

			long returnValue = tree->Delete(1);
			Assert::AreEqual(ERROR_SUCCESS, returnValue);

			int value;
			returnValue = tree->Find(1, value);
			Assert::AreEqual(ERROR_NOT_FOUND, returnValue);
			returnValue = tree->Find(2, value);
			Assert::AreEqual(ERROR_SUCCESS, returnValue);
			Assert::AreEqual(200, value);
		}

		/*
		      5
		   3     7
		  2 4   6 8
		*/
		BinaryTree * CreateStandardBinaryTree()
		{
			BinaryTree * tree = new (std::nothrow) BinaryTree();

			tree->Insert(5, 5);
			tree->Insert(3, 3);
			tree->Insert(7, 7);
			tree->Insert(2, 2);
			tree->Insert(4, 4);
			tree->Insert(6, 6);
			tree->Insert(8, 8);

			return tree;
		}

		TEST_METHOD(DeleteRightLeaf)
		{
			std::unique_ptr<BinaryTree> tree(CreateStandardBinaryTree());

			tree->Delete(8);

			int value;
			long err = tree->Find(2, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(3, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(4, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(5, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(6, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(7, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(8, value);
			Assert::AreEqual(ERROR_NOT_FOUND, err);
		}

		TEST_METHOD(DeleteLeftLeaf)
		{
			std::unique_ptr<BinaryTree> tree(CreateStandardBinaryTree());

			tree->Delete(2);

			int value;
			long err = tree->Find(2, value);
			Assert::AreEqual(ERROR_NOT_FOUND, err);
			err = tree->Find(3, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(4, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(5, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(6, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(7, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(8, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
		}

		TEST_METHOD(DeleteRightInternal)
		{
			std::unique_ptr<BinaryTree> tree(CreateStandardBinaryTree());

			tree->Delete(7);

			int value;
			long err = tree->Find(2, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(3, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(4, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(5, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(6, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(7, value);
			Assert::AreEqual(ERROR_NOT_FOUND, err);
			err = tree->Find(8, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
		}

		TEST_METHOD(DeleteLeftInternal)
		{
			std::unique_ptr<BinaryTree> tree(CreateStandardBinaryTree());

			tree->Delete(3);

			int value;
			long err = tree->Find(2, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(3, value);
			Assert::AreEqual(ERROR_NOT_FOUND, err);
			err = tree->Find(4, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(5, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(6, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(7, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(8, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
		}

		TEST_METHOD(DeleteHead)
		{
			std::unique_ptr<BinaryTree> tree(CreateStandardBinaryTree());

			tree->Delete(5);

			int value;
			long err = tree->Find(2, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(3, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(4, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(5, value);
			Assert::AreEqual(ERROR_NOT_FOUND, err);
			err = tree->Find(6, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(7, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
			err = tree->Find(8, value);
			Assert::AreEqual(ERROR_SUCCESS, err);
		}

		// Just run and see if it dies
		TEST_METHOD(ChaosMonkey)
		{
			for (int i = 0; i < 1000; i++)
			{
				std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

				for (int nodes = 0; nodes < MaxNodes; nodes++)
				{
					int key = rand() % MaxNodes;
					int value = rand();

					tree->Insert(key, value);

					key = rand() % MaxNodes;

					tree->Delete(key);
				}

				nodeIndex = 0;
				tree->EvaluateInOrder(EvalFunction);

				for (int j = 0; j < nodeIndex-1; j++)
				{
					// Make sure they are in order
					Assert::IsTrue(nodeArray[j]->Key < nodeArray[j + 1]->Key);
				}
			}
		}

	};
}