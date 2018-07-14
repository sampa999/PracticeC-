#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\BinaryTree\BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTree_Tests
{		
	TEST_CLASS(Test1)
	{
	public:
		
		TEST_METHOD(InstantiateTree)
		{
			BinaryTree * tree = new BinaryTree();

			Assert::IsNotNull(tree);
		}

		TEST_METHOD(Insert)
		{
			BinaryTree * tree = new BinaryTree();

			Assert::IsNotNull(tree);

			long err = tree->Insert(0, 100);

			Assert::AreEqual(ERROR_SUCCESS, err);
		}

	};
}