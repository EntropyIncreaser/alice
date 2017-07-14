#ifndef ALICE_DYNAMIC_BIT_HPP
#define ALICE_DYNAMIC_BIT_HPP

#include <vector>
#include <utility>

#include "suffix.hpp"
#include "bitmath.hpp"

namespace alice {

template <class T, class Combination = std::plus<T>, class Container = std::vector<T> >
class dynamic_binary_indexed_tree {
private:
	Container tree;
	Combination comb;

public:
	typedef T value_type;
	typedef Container container_type;
	typedef Combination combination_type;
	typedef std::size_t size_type;

	explicit
	dynamic_binary_indexed_tree(const combination_type& comb = combination_type(),
		const container_type& origin = container_type()) : comb(comb), tree(origin) {
		for (size_type i = 1; i < tree.size(); ++i)
			for (size_type bit = low_bit(i + 1) >> 1; bit; bit >>= 1)
				tree[i] = comb(tree[i], tree[i - bit]);
	}

	dynamic_binary_indexed_tree(const dynamic_binary_indexed_tree& copied) :
		tree(copied.tree), comb(copied.comb) {}

#ifdef ALICE_CPP11
	dynamic_binary_indexed_tree(dynamic_binary_indexed_tree&& rhs) :
		tree(std::move(rhs.tree)), comb(std::move(comb)) {}
#endif
};

}

#endif // ALICE_DYNAMIC_BIT_HPP
