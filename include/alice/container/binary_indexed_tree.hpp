#ifndef ALICE_BIT_HPP
#define ALICE_BIT_HPP

#include <cstddef>

#include <algorithm>
#include <functional>

#include "suffix.hpp"

namespace alice {

inline std::size_t low_bit(std::size_t x) 
{ return x & (~x + 1); }

template <class T, std::size_t N, class Combination = std::plus<T> >
class binary_indexed_tree {
private:
	T tree[N];

public:
	typedef T value_type;
	typedef std::size_t size_type;

	binary_indexed_tree()
#ifdef ALICE_CPP11
	= default;
#else
	{}
#endif

	binary_indexed_tree(const binary_indexed_tree& copied) {
		std::copy(tree, tree + N, copied.tree);
	}

	binary_indexed_tree(const value_type& repeated_value);

	template <class InputIterator>
	binary_indexed_tree(InputIterator first);

	T query(size_type at);

	void change(size_type at);
};

}

#endif // ALICE_BIT_HPP
