#ifndef ALICE_DYNAMIC_BIT_HPP
#define ALICE_DYNAMIC_BIT_HPP

#include <vector>

namespace alice {

template <class T, class Combination = std::plus<T>, class Container = std::vector<T> >
class dynamic_binary_indexed_tree {
private:
	Container origin, tree;
	Combination comb;

public:
	typedef T value_type;
	typedef Container container_type;
	typedef std::size_t size_type;

};

}

#endif // ALICE_DYNAMIC_BIT_HPP
