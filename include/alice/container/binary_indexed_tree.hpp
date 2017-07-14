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
	Combination comb;

public:
	typedef T value_type;
	typedef std::size_t size_type;

	explicit
	binary_indexed_tree(const Combination& comb = Combination()) : comb(comb) {}

	binary_indexed_tree(const binary_indexed_tree& copied, const Combination& comb = Combination()) : comb(comb) {
		std::copy(tree, tree + N, copied.tree);
	}

#ifdef ALICE_CPP11
	binary_indexed_tree(binary_indexed_tree&& rhs)
	{ std::swap(tree, rhs.tree); }
#endif

	binary_indexed_tree(const value_type& repeated_value,
		const Combination& comb = Combination()) : comb(comb) {
		tree[0] = repeated_value;
		for (size_type i = 2; i <= N; i <<= 1)
			tree[i - 1] = comb(tree[(i >> 1) - 1], tree[(i >> 1) - 1]);
		for (size_type i = 1; i < N; ++i)
			tree[i] = tree[low_bit(i + 1) - 1];
	}

	template <class InputIterator>
	binary_indexed_tree(InputIterator first, const Combination& comb = Combination());

	value_type query(size_type at) {
		value_type ret = tree[at - 1];
		for (at -= low_bit(at); at; at -= low_bit(at))
			ret = comb(tree[at - 1], ret);
		return ret;
	}

	void change(size_type at, const value_type& v) {
		for (; at <= N; at += low_bit(at))
			tree[at - 1] = comb(tree[at - 1], v);
	}
};

template <class T, std::size_t N, class Combination>
template <class InputIterator>
binary_indexed_tree<T, N, Combination>::
	binary_indexed_tree(InputIterator first,
		const Combination& comb = Combination()) : comb(comb) {
		for (size_type i = 0; i < N; ++i) {
			tree[i] = *(first++);
			for (size_type bit = low_bit(i + 1) >> 1; bit; bit >>= 1)
				tree[i] = comb(tree[i], tree[i - bit]);
		}
}

}

#endif // ALICE_BIT_HPP
