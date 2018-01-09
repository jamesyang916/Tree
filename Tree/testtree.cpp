#include <tree.h>

void test_tree()
{
    using namespace jameslibrary;
    Tree<int, detail::Node> oTree{ 0 };
    oTree.addNode(1, 0);
    oTree.addNode(2, 0);
    oTree.addNode(3, 1);
    oTree.addNode(4, 10); // Should not do anything
    oTree.printTree();
    Tree<int, detail::Node> oTree2(2);
    oTree2.printTree();
    oTree2 = oTree;
    oTree2.printTree();
    int tmp;
    std::cin >> tmp;
}

