#include "tree.h"


using namespace jameslibrary;

int main()
{
	Tree<int>* T = new Tree<int>(0);

	(*T).addNode(1, 0);
	(*T).addNode(2, 0);
	(*T).addNode(3, 1);
	(*T).addNode(4, 10); // Should not do anything
	
	(*T).printTree();

	Tree<int> T2(2);
	T2.printTree();

	T2 = *T;

	T2.printTree();

	delete T;

	int tmp;
	std::cin >> tmp;

	return 0;
}