#pragma once
#include <deque>
#include <iostream>

// n_aryTree Class Declaration
namespace jameslibrary {
template <class T, int n = 2>
class n_aryTree {
public:
    n_aryTree()
        : nodes(1, T()) {}
    n_aryTree(T const& x)
        : nodes(2, x) {}
    n_aryTree(n_aryTree<T> const& t)
        : nodes(t.nodes) {}
    n_aryTree<T>& operator=(n_aryTree<T> const& t)
    {
        nodes = t.nodes;
    }

    std::deque<T>::const_iterator
    findPos(T const&) const;

    void max_heapify();

private:
    std::deque<T> nodes;
};
}

// n_aryTree Class Definition
namespace jameslibrary {
template <class T>
std::deque<T>::const_iterator
n_aryTree<T>::findPos(T const& x) const
{
}


}