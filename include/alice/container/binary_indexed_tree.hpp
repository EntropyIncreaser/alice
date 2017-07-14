#ifndef ALICE_BIT_HPP
#define ALICE_BIT_HPP

#include <cstddef>

#include <algorithm>
#include <functional>

#include "suffix.hpp"

namespace alice {

inline std::size_t low_bit(std::size_t x)
{ return x & (~x + 1); }

template<class T, class Combination>
inline T self_combinate(Combination comb, const T& t)
{ return comb(t, t); }

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
		for (size_type i = 0; i < N; ++i)
			if (i & 1)
				tree[i] = self_combinate(comb, tree[(low_bit(i + 1) >> 1) - 1]);
			else
				tree[i] = repeated_value;
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

}

#endif // ALICE_BIT_HPP
