#include "TBinaryTree.h"
#include <iostream>


int main()
{
	TBinaryTree tree;

	try
	{
		tree.Insert(10);
		tree.Insert(20);
		tree.Insert(1);
		tree.Insert(2);
		tree.Insert(15);

		tree.Insert(-10);
		tree.Insert(10);
	}
	catch (const TExistElementException & e)
	{
		std::cout << e.what();
	}

	std::cout << tree;


	try
	{
		TBinaryTree::TNode * found1 = tree.Find(2);
		if (found1)
			std::cout << found1->Data << std::endl;
		TBinaryTree::TNode * found2 = tree.Find(13);
		if (found2)
			std::cout << found2->Data << std::endl;
	}
	catch (const TNotFoundException & e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
}
