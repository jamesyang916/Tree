#include <tree.h>

/* Node Class Definition */
namespace jameslibrary {
namespace detail {
/* Node Default Constructor */
Node::Node()
    : idx(0), parent(nullptr), childList()
{}

/* Node Constructor */
Node::Node(int i)
    : idx(i), parent(nullptr), childList()
{}

/* Node Copy Constructor */
Node::Node(Node const& node)
    : idx(node.idx), parent(node.parent),
      childList(node.childList)
{}

/* Node Destructor */
Node::~Node()
{
    for (auto it = childList.begin();
         it != childList.end(); ++it) {
        delete *it;
    }

    childList.clear();
}

/* Node Copy Assignment */
Node const& Node::operator=(Node const& node)
{
    idx = node.idx;
    parent = node.parent;
    childList = node.childList;
    return *this;
}

/* Node Operator == */
bool Node::operator==(Node const& node) const
{
    return (idx == node.idx);
}

/* Node Operator != */
bool Node::operator!=(Node const& node) const
{
    return !(*this == node);
}

/* Find Position of node (child) in childList
Linear search (as of now)
*/
auto Node::findPos(Node const& node) const
{
    auto it = childList.begin();

    for (it; it != childList.end(); ++it) {
        if (*(*it) == node) {
            break;
        }
    }

    return it;
}

/* Change Parent Node Ptr */
void Node::changeParent(Node& p)
{
    parent = &p;
}

/* Add Child */
void Node::addChild(Node& child)
{
    if (findPos(child) == childList.end()) {
        childList.push_back(&child);
    }
}

/* Remove Child
There are unique ptrs to each child
See addChild()
*/
void Node::removeChild(Node& child)
{
    auto i = findPos(child);

    if (i != childList.end()) {
        childList.erase(i);
    }
}

/* Clear childList */
void Node::clearChildList()
{
    childList.clear();
}

/* Get Index */
int Node::getIndex() const
{
    return idx;
}

/* Get Parent Node Ptr */
Node* Node::getParent() const

{
    return parent;
}

/* Get childList */
std::list<Node*> const& Node::getChildList() const
{
    return childList;
}

} // end of detail
} // end of jameslibrary
