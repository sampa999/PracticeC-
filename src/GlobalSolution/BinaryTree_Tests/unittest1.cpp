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
			Assert::AreEqual(0, nodeArray[0]->get_Key());
			Assert::AreEqual(100, nodeArray[0]->get_Value());
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
			Assert::AreEqual(9, nodeArray[0]->get_Key());
			Assert::AreEqual(99, nodeArray[0]->get_Value());
			Assert::AreEqual(10, nodeArray[1]->get_Key());
			Assert::AreEqual(100, nodeArray[1]->get_Value());
			Assert::AreEqual(11, nodeArray[2]->get_Key());
			Assert::AreEqual(101, nodeArray[2]->get_Value());
		}

		TEST_METHOD(CheckDepthOfChildrenBalancedTree)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			nodeIndex = 0;

			tree->Insert(10, 100);
			tree->Insert(9, 99);
			tree->Insert(11, 101);
			tree->UpdateDepthOfChildren();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(3, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
		}

		TEST_METHOD(CheckDepthOfChildrenAfterOneSideDeleted)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			nodeIndex = 0;

			tree->Insert(10, 100);
			tree->Insert(9, 99);
			tree->Insert(11, 101);
			tree->Delete(9);
			tree->UpdateDepthOfChildren();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(2, nodeIndex);
			Assert::AreEqual(1, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[1]->DepthOfChildren);
		}

		TEST_METHOD(CheckDepthOfChildrenAfterTwoSideDeleted)
		{
			std::unique_ptr<BinaryTree> tree(new (std::nothrow) BinaryTree());

			nodeIndex = 0;

			tree->Insert(10, 100);
			tree->Insert(9, 99);
			tree->Insert(11, 101);
			tree->Delete(9);
			tree->Delete(11);

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(1, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
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

		BinaryTree * CreateTree(int * node, int nodeCount)
		{
			BinaryTree * tree = new (std::nothrow) BinaryTree();

			for (int i = 0; i < nodeCount; i++)
			{
				tree->Insert(node[i], i);
			}

			return tree;
		}

		/*
		      5
		   3     7
		  2 4   6 8
		*/
		BinaryTree * CreateStandardBinaryTree()
		{
			int keys[7] = { 5,3,7,2,4,6,8 };

			return CreateTree(keys, 7);
		}

		void Verify15TreeIsCorrect()
		{
			Assert::AreEqual(15, nodeIndex);

			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[4]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[6]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[8]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[0xA]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[0xC]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[0xE]->DepthOfChildren);

			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[5]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[9]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[0xD]->DepthOfChildren);

			Assert::AreEqual(2, nodeArray[3]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[0xB]->DepthOfChildren);

			Assert::AreEqual(3, nodeArray[7]->DepthOfChildren);
		}

		/*
		Insert in order from root. i.e. insert 7, then 3B, then 159D, then 02468ACE
		This insures it is always balanced and never has to adjust
                    7
              3           B
          1      5     9     D
         0 2    4 6   8 A   C E
		*/
		TEST_METHOD(CheckDepthOfChildrenOnBalancedInsert)
		{
			int nodeKeys[15] = { 7, 3, 0xB, 1, 5, 9, 0xD, 0, 2, 4, 6, 8, 0xA, 0xC, 0xE };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 15));

			tree->UpdateDepthOfChildren();

			tree->Rebalance();

			nodeIndex = 0;

			tree->EvaluateInOrder(&EvalFunction);

			Verify15TreeIsCorrect();
		}

		/*
		Insert in key order. i.e. 0123456789ABCDE
		This insures it has to rebalance the maximum number of times.
                    7
              3           B
          1      5     9     D
         0 2    4 6   8 A   C E
		*/
		TEST_METHOD(CheckDepthOfChildrenOnKeyOrderInsert)
		{
			int nodeKeys[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 15));

			tree->UpdateDepthOfChildren();

			nodeIndex = 0;

			tree->EvaluateInOrder(&EvalFunction);

			Verify15TreeIsCorrect();
		}

		/*
		Insert in reverse key order. i.e. EDCBA9876543210
		This insures it has to rebalance the maximum number of times.
                    7
              3           B
          1      5     9     D
         0 2    4 6   8 A   C E
		*/
		TEST_METHOD(CheckDepthOfChildrenOnReverseKeyOrderInsert)
		{
			int nodeKeys[15] = { 0xE, 0xD, 0xC, 0xB, 0xA, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 15));

			tree->UpdateDepthOfChildren();

			nodeIndex = 0;

			tree->EvaluateInOrder(&EvalFunction);

			Verify15TreeIsCorrect();
		}

		TEST_METHOD(RebalanceTreeWith3LeftNodes)
		{
			int nodeKeys[3] = { 3,2,1 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 3));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(3, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith3RightNodes)
		{
			int nodeKeys[3] = { 1,2,3 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 3));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(3, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith4LeftNodes)
		{
			int nodeKeys[4] = { 4,3,2,1 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 4));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(4, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[3]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith4RightNodes)
		{
			int nodeKeys[4] = { 1,2,3,4 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 4));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(4, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[3]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith5LeftNodes)
		{
			int nodeKeys[] = { 5,4,3,2,1 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 5));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(5, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[3]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[4]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith5RightNodes)
		{
			int nodeKeys[] = { 1,2,3,4,5};

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 5));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(5, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[3]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[4]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith6LeftNodes)
		{
			int nodeKeys[] = { 6,5,4,3,2,1 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 6));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(6, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[3]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[4]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[5]->DepthOfChildren);
		}

		TEST_METHOD(RebalanceTreeWith6RightNodes)
		{
			int nodeKeys[] = { 1,2,3,4,5,6 };

			std::unique_ptr<BinaryTree> tree(CreateTree(nodeKeys, 6));

			nodeIndex = 0;

			tree->Rebalance();

			tree->EvaluateInOrder(&EvalFunction);

			Assert::AreEqual(6, nodeIndex);
			Assert::AreEqual(0, nodeArray[0]->DepthOfChildren);
			Assert::AreEqual(1, nodeArray[1]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[2]->DepthOfChildren);
			Assert::AreEqual(2, nodeArray[3]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[4]->DepthOfChildren);
			Assert::AreEqual(0, nodeArray[5]->DepthOfChildren);
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
					Assert::IsTrue(nodeArray[j]->get_Key() < nodeArray[j + 1]->get_Key());
				}
			}
		}

	};
}