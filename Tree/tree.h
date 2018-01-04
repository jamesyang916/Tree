#pragma once
#include "node.h"
#include <deque>
#include <iostream>

/* Tree Class Declaration */
namespace jameslibrary
{
	template <class T>
	class Tree
	{
	public:
		Tree()						// Default Constructor
			: T_objects(), root(nullptr) {}
		Tree(T const & r)			// Constructor
			: T_objects(1, r)
		{
			root = new Node(0);
		}
		Tree(Tree<T> const & t);	// Copy constructor
		virtual Tree<T> const &		// Copy assignment
			operator=(Tree<T> const &);
		virtual ~Tree();			// Destructor

		inline void clear();				// Clears tree

		Node* findNode(T const &) const;	// Finds first Node
											// matching data

		void addNode(T const &, T const &); // Add node given new
											// data and parent data

		inline bool empty() const;			// Returns whether tree
											// is empty

		inline void printTree() const;		// Prints Tree

	private:
		// Helper functions
		void copy(Node*);
		Node* findNode(T const &, Node *) const;
		void printTree(Node const *) const;
			
		std::deque<T> T_objects;
		Node* root;
	};
}

/* Tree Class Definition */
namespace jameslibrary
{
	/* Deep Copy from another Tree */
	template <class T>
	void Tree<T>::copy(Node* r)
	{
		auto childList = (*r).getChildList();
		(*r).clearChildList();
		for (auto it = childList.begin();
			it != childList.end(); ++it)
		{
			T child_data = T_objects[(**it).getIndex()];
			T parent_data = T_objects[(*r).getIndex()];
			addNode(child_data, parent_data);	// SLOW but accurate
												// because trees are
												// all made like this
		}

		for (auto it = childList.begin();
			it != childList.end(); ++it)
		{
			copy(*it);
		}
	}

	/* Copy Constructor */
	template <class T>
	Tree<T>::Tree(Tree<T> const & t)
		: T_objects(t.T_objects)
	{
		if (t.empty())
			root = nullptr;
		root = new Node(*t.root);
		copy(root);
	}

	/* Copy assignment */
	template <class T>
	Tree<T> const & Tree<T>::operator=(Tree<T> const & t)
	{
		// Copy only if not self-assignment
		if (this != &t)
		{
			clear();					// deallocate current tree
			T_objects = t.T_objects;
			root = new Node(*t.root);	// reallocate for new tree
			copy(root);
		}
		return *this;
	}

	/* Clear Tree */
	template <class T>
	inline void Tree<T>::clear()
	{
		delete root;
		root = nullptr;
		T_objects.clear();
	}

	/* Destructor */
	template <class T>
	Tree<T>::~Tree()
	{
		clear();
	}

	/* Finds the first Node corresponding to T object x 
	Returns pointer to found node.
	If not found, return nullptr.	
	*/
	template <class T>
	Node* Tree<T>::findNode(T const & x, Node* root_ptr) const
	{
		Node* foundNode = nullptr;
		// Check if root_ptr is nullptr
		if (root_ptr == nullptr)
			return nullptr;
		
		// Check if root corresonds to x
		int idx = (*root_ptr).getIndex();
		if (T_objects[idx] == x)
			return root_ptr;

		// If not, recurse through every child
		auto childList = (*root_ptr).getChildList();
		for (auto it = childList.begin(); 
			it != childList.end(); ++it)
		{
			foundNode = findNode(x, (*it));
			// If node has been found,
			if (foundNode != nullptr)
				break;
		}

		return foundNode;
	}

	template <class T>
	Node* Tree<T>::findNode(T const & x) const
	{
		return findNode(x, root);
	}

	/* Add New Node 
	It does not matter if another node exists with data x.
	Always new Node created.
	*/
	template <class T>
	void Tree<T>::addNode(T const & x, // new data
						  T const & p  // new parent
							)
	{
		// Check if parent exists
		Node* parent = findNode(p);
		if (parent == nullptr)
		{
			// Throw exception
			return;
		}

		// Add x to the deque of objects
		T_objects.push_back(x);
		int idx = T_objects.size() - 1; // index of x in T_objects
										// Careful with multiprocess	
		Node* newNode = new Node(idx);

		// Add *parent to newNode
		(*newNode).changeParent(*parent);

		// Add newNode to *parent
		(*parent).addChild(*newNode);
	}

	/* Is tree empty? */
	template <class T>
	inline bool Tree<T>::empty() const
	{
		return T_objects.empty();
	}

	/* Print Tree */
	template <class T>
	void Tree<T>::printTree(Node const * r) const
	{
		if (r != nullptr)
		{
			std::cout << "Data: " << T_objects[(*r).getIndex()] 
				<< std::endl;

			std::cout << "Parent: ";
			if ((*r).getParent() != nullptr)
			{
				Node* par = (*r).getParent();
				std::cout << T_objects[(*par).getIndex()];
			}
			std::cout << std::endl;

			std::cout << "Children:";
			auto childList = (*r).getChildList();
			for (auto x : childList)
			{
				std::cout << T_objects[(*x).getIndex()] << ", ";
			}
			std::cout << '\n' << std::endl;

			// Recurse through each child
			for (auto it = childList.begin();
				it != childList.end(); ++it)
			{
				printTree(*it);
			}
			std::cout << std::endl;
		}
	}

	/* Print Tree */
	template <class T>
	inline void Tree<T>::printTree() const	
	{
		printTree(root);
	}

}

