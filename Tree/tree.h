#pragma once
#include <list>
#include <deque>
#include <memory>
#include <iostream>

/* Tree Class Declaration */
namespace jameslibrary {
namespace detail {

/* Node Class Declaration */
class Node {
public:
    Node();
    Node(int);
    Node(Node const&);
    ~Node();

    Node const& operator=(Node const&);
    bool operator==(Node const&) const;
    bool operator!=(Node const&) const;

    auto findPos(Node const&) const;

    void changeParent(Node&);
    void addChild(Node&);
    void removeChild(Node&);
    void clearChildList();

    int getIndex() const;
    Node* getParent() const;
    std::list<Node*> const& getChildList() const;

private:
    int idx;
    Node* parent;
    std::list<Node*> childList;
};

class binaryNode {
};

}  // end of detail

template <class T, class T_Node>
class Tree {
public:
    Tree()                      // Default Constructor
        : T_objects(), root(nullptr) {}
    Tree(T const& r)            // Constructor
        : T_objects(1, r)
    {
        root = std::unique_ptr<T_Node>(new T_Node(0));
    }
    Tree(Tree<T, T_Node> const& t);     // Copy constructor
    Tree<T, T_Node> const&      // Copy assignment
    operator=(Tree<T, T_Node> const&);
    ~Tree();            // Destructor

    inline void clear();                // Clears tree


    void addNode(T const&, T const&);   // Add node given new data and parent data

    inline bool empty() const;          // Returns whether tree is empty

    inline void printTree() const;      // Prints Tree

private:
    // Helper functions
    void copy(T_Node*);
    T_Node* findNode(T const&, T_Node*) const;
    T_Node* findNode(T const&) const;     // Finds first Node
    // matching data
    void printTree(T_Node const*) const;

    std::deque<T> T_objects;
    std::unique_ptr<T_Node> root;
};
}

/* Binary Tree Specialization Declaration */
namespace jameslibrary {
using binaryNode = detail::binaryNode;
template <class T>
class Tree<T, binaryNode> {
public:
    Tree()                      // Default Constructor
        : T_objects(1) {}
    Tree(T const& r)            // Constructor
        : T_objects(1, r) {}
    Tree(Tree<T, binaryNode> const& t);     // Copy constructor
    Tree<T, binaryNode> const&      // Copy assignment
    operator=(Tree<T, binaryNode> const&);

    inline void clear();                // Clears tree


    void addNode(T const&, T const&);   // Add node given new data and parent data

    inline bool empty() const;          // Returns whether tree is empty

    inline void printTree() const;      // Prints Tree

private:
    // Helper functions
    void copy(binaryNode*);
    binaryNode* findNode(T const&, binaryNode*) const;
    binaryNode* findNode(T const&) const;     // Finds first Node
    // matching data
    void printTree(binaryNode const*) const;

    std::deque<T> T_objects;
};
}



/* Tree Class Definition */
namespace jameslibrary {
/* Deep Copy from another Tree */
template <class T, class T_Node>
void Tree<T, T_Node>::copy(T_Node* r)
{
    auto childList = (*r).getChildList();
    (*r).clearChildList();

    for (auto it = childList.begin();
         it != childList.end(); ++it) {
        T child_data = T_objects[(**it).getIndex()];
        T parent_data = T_objects[(*r).getIndex()];
        addNode(child_data, parent_data);   // SLOW but accurate
        // because trees are
        // all made like this
    }

    for (auto it = childList.begin();
         it != childList.end(); ++it) {
        copy(*it);
    }
}

/* Copy Constructor */
template <class T, class T_Node>
Tree<T, T_Node>::Tree(Tree<T, T_Node> const& t)
    : T_objects(t.T_objects)
{
    if (t.empty()) {
        root = std::unique_ptr<T_Node>(nullptr);
    }

    root = std::unique_ptr<T_Node>(new T_Node(*t.root));
    copy(root.get());
}

/* Copy assignment */
template <class T, class T_Node>
Tree<T, T_Node> const& Tree<T, T_Node>::operator=(Tree<T, T_Node> const& t)
{
    // Copy only if not self-assignment
    if (this != &t) {
        clear();                    // deallocate current tree
        T_objects = t.T_objects;
        root = std::unique_ptr<T_Node>(new T_Node(*t.root));   // reallocate for new tree
        copy(root.get());
    }

    return *this;
}

/* Clear Tree */
template <class T, class T_Node>
inline void Tree<T, T_Node>::clear()
{
    root.reset(nullptr);
    T_objects.clear();
}

/* Destructor */
template <class T, class T_Node>
Tree<T, T_Node>::~Tree()
{
    clear();
}

/* Finds the first Node corresponding to T object x
Returns pointer to found node.
If not found, return nullptr.
*/
template <class T, class T_Node>
typename T_Node* Tree<T, T_Node>::findNode(T const& x, T_Node* root_ptr) const
{
    T_Node* foundNode = nullptr;

    // Check if root_ptr is nullptr
    if (root_ptr == nullptr) {
        return nullptr;
    }

    // Check if root corresonds to x
    int idx = (*root_ptr).getIndex();

    if (T_objects[idx] == x) {
        return root_ptr;
    }

    // If not, recurse through every child
    auto childList = (*root_ptr).getChildList();

    for (auto it = childList.begin();
         it != childList.end(); ++it) {
        foundNode = findNode(x, (*it));

        // If node has been found,
        if (foundNode != nullptr) {
            break;
        }
    }

    return foundNode;
}

template <class T, class T_Node>
typename T_Node* Tree<T, T_Node>::findNode(T const& x) const
{
    return findNode(x, root.get());
}

/* Add New Node
It does not matter if another node exists with data x.
Always new Node created.
*/
template <class T, class T_Node>
void Tree<T, T_Node>::addNode(T const& x,  // new data
                              T const& p   // new parent
                             )
{
    // Check if parent exists
    T_Node* parent = findNode(p);

    if (parent == nullptr) {
        // Throw exception
        return;
    }

    // Add x to the deque of objects
    T_objects.push_back(x);
    int idx = T_objects.size() - 1; // index of x in T_objects
    // Careful with multiprocess
    T_Node* newNode = new T_Node(idx);
    // Add *parent to newNode
    (*newNode).changeParent(*parent);
    // Add newNode to *parent
    (*parent).addChild(*newNode);
}

/* Is tree empty? */
template <class T, class T_Node>
inline bool Tree<T, T_Node>::empty() const
{
    return T_objects.empty();
}

/* Print Tree */
template <class T, class T_Node>
void Tree<T, T_Node>::printTree(T_Node const* r) const
{
    if (r != nullptr) {
        std::cout << "Data: " << T_objects[(*r).getIndex()]
                  << std::endl;
        std::cout << "Parent: ";

        if ((*r).getParent() != nullptr) {
            T_Node* par = (*r).getParent();
            std::cout << T_objects[(*par).getIndex()];
        }

        std::cout << std::endl;
        std::cout << "Children:";
        auto childList = (*r).getChildList();

        for (auto x : childList) {
            std::cout << T_objects[(*x).getIndex()] << ", ";
        }

        std::cout << '\n' << std::endl;

        // Recurse through each child
        for (auto it = childList.begin();
             it != childList.end(); ++it) {
            printTree(*it);
        }

        std::cout << std::endl;
    }
}

/* Print Tree */
template <class T, class T_Node>
inline void Tree<T, T_Node>::printTree() const
{
    printTree(root.get());
}

}

/* Binary Tree Definition */
namespace jameslibrary {
// Copy Constructor
template <class T>
Tree<T, binaryNode>::Tree(Tree<T, binaryNode> const& t)
    : T_objects(t.T_objects) {}

// Copy Assignment
template <class T>
Tree<T, binaryNode> const&
Tree<T, binaryNode>::operator=(Tree<T, binaryNode> const& t)
{
    if (this != &t) {
        T_objects = t.T_objects;
    }

    return *this;
}

// Clear Tree
template <class T>
void Tree<T, binaryNode>::clear()
{
    T_objects.clear();
}

// Is Empty?
template <class T>
bool Tree<T, binaryNode>::empty() const
{
    return T_objects.empty();
}


}
/* Tree Test Functions */
void test_tree();


