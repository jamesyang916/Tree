#include "tree.h"
#include <iostream>

template <class T>
class Trial
{
public:
	Trial(T const & t)
		:  data(t) {}
	inline T getData() const;
private:
	T data;
};

template <class T>
inline T Trial<T>::getData() const
{
	return data;
}


using namespace jameslibrary;

void test()
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
}
int main()
{
	Tree<int> T1(0);
	Tree<int> T2(1);

	test();

	int tmp;
	std::cin >> tmp;

	return 0;
}