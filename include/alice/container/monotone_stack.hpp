#ifndef ALICE_MONOTONE_STACK_HPP
#define ALICE_MONOTONE_STACK_HPP

#include <cstddef>

#include <deque>
#include <functional>

namespace alice {

template <class T, class Compare = std::less<T>,
          class ContainerT = std::deque<T>,
          class ContainerInteger = std::deque<std::size_t> >
class monotone_stack {
public:
	typedef T                value_type;
	typedef const T&         const_reference;
	typedef ContainerT       value_container_type;
	typedef ContainerInteger integer_container_type;

private:
	Compare comp;
	value_container_type stk;
	integer_container_type count;

public:
	monotone_stack(Compare comp = Compare()) : comp(comp) {}

	void push(const value_type& x) {
		if (stk.empty()) {
			stk.push_back(x);
			count.push_back(1);
		} else {
			if (comp(stk.back(), x))
				++count.back();
			else {
				stk.push_back(x);
				count.push_back(1);
			}
		}
	}

	void pop() {
		if (!--count.back()) {
			count.pop_back();
			stk.pop_back();
		}
	}

	const_reference min() const {
		return stk.back();
	}
};

}

#endif // ALICE_MONOTONE_STACK_HPP
