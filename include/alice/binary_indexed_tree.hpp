#ifndef ALICE_BIT_HPP
#define ALICE_BIT_HPP

#include <cstddef>

#include <algorithm>
#include <functional>

namespace alice {

inline std::size_t low_bit(std::size_t x) 
{ return x & (~x + 1); }

template <class T, std::size_t N, class Combination = std::plus<T> >
class binary_indexed_tree {
private:
	array<T, N> tree;

public:
	typedef T value_type;
	typedef std::size_t size_type;

	binary_indexed_tree() noexcept(std::is_nothrow_default_constructible<value_type>::value) 
#if __cplusplus >= 11
	{}

	template <class InputIterator>
	binary_indexed_tree(InputIterator first) noexcept(std::is_nothrow_copy_constructible<value_type>::value) {

	}
};

}

#endif // ALICE_BIT_HPP
