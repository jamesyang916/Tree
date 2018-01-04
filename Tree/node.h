#pragma once
#include <list>

/* Node Class Declaration */
namespace jameslibrary
{
	class Node
	{
	public:
		Node();
		Node(int);
		Node(Node const &);
		~Node();

		Node const & operator=(Node const &);
		bool operator==(Node const &) const;
		bool operator!=(Node const &) const;

		auto findPos(Node const &) const;

		inline void changeParent(Node const &);
		inline void addChild(Node const &);
		inline void removeChild(Node const &);
		inline void clearChildList();

		inline int getIndex() const;
		inline Node* getParent() const;
		inline std::list<Node*> const & getChildList() const;

	private:
		int idx;
		Node* parent;
		std::list<Node*> childList;
	};
}

/* Node Class Definition */
namespace jameslibrary
{
	/* Node Default Constructor */
	Node::Node()
		: idx(0), parent(nullptr), childList()
	{}

	/* Node Constructor */
	Node::Node(int i)
		:	idx(i), parent(nullptr), childList()
	{}

	/* Node Copy Constructor */
	Node::Node(Node const & node)
		: idx(node.idx), parent(node.parent),
		childList(node.childList)
	{}
	
	/* Node Destructor */
	Node::~Node()
	{
		for (auto it = childList.begin();
			it != childList.end(); ++it)
		{
			delete *it;
		}
		childList.clear();
	}

	/* Node Copy Assignment */
	Node const & Node::operator=(Node const & node)
	{
		idx = node.idx;
		parent = node.parent;
		childList = node.childList;

		return *this;
	}

	/* Node Operator == */
	bool Node::operator==(Node const & node) const
	{
		return (idx == node.idx);
	}

	/* Node Operator != */
	bool Node::operator!=(Node const & node) const
	{
		return !(*this == node);
	}

	/* Find Position of node (child) in childList 
	Linear search (as of now)	
	*/
	auto Node::findPos(Node const & node) const
	{
		auto it = childList.begin();
		for (it; it!=childList.end(); ++it)
		{
			if (*(*it) == node)
				break;
		}
		return it;
	}

	/* Change Parent Node Ptr */
	inline void Node::changeParent(Node const & p)
	{
		parent = const_cast<Node*>(&p);
	}

	/* Add Child */
	inline void Node::addChild(Node const & child)
	{
		if (findPos(child) == childList.end())
			childList.push_back(const_cast<Node*>(&child));
	}

	/* Remove Child 
	There are unique ptrs to each child
	See addChild()
	*/
	inline void Node::removeChild(Node const & child)
	{
		auto i = findPos(child);
		if (i != childList.end())
			childList.erase(i);
	}

	/* Clear childList */
	inline void Node::clearChildList()
	{
		childList.clear();
	}

	/* Get Index */
	inline int Node::getIndex() const
	{
		return idx;
	}
	
	/* Get Parent Node Ptr */
	inline Node* Node::getParent() const
	
	{
		return parent;
	}

	/* Get childList */
	inline std::list<Node*> const & Node::getChildList() const
		{
			return childList;
		}

}

