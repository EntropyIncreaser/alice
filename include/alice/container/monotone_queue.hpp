#ifndef ALICE_MONOTONE_QUEUE_HPP
#define ALICE_MONOTONE_QUEUE_HPP

#include <cstddef>

#include <deque>
#include <functional>

namespace alice {

template <class T, class Compare = std::less<T>,
class ContainerT = std::deque<T>,
class ContainerInteger = std::deque<std::size_t> >
class monotone_queue {
public:
	typedef T                value_type;
	typedef const T&         const_reference;
	typedef ContainerT       value_container_type;
	typedef ContainerInteger integer_container_type;

private:
	Compare comp;
	value_container_type que;
	integer_container_type count;

public:
	monotone_queue(Compare comp = Compare()) : comp(comp) {}

	void push(const value_type& x) {
		std::size_t cnt = 1;
		while (!que.empty()) {
			if (comp(x, que.back())) {
				que.pop_back();
				cnt += count.back();
				count.pop_back();
			} else
				break;
		}
		que.push_back(x);
		count.push_back(cnt);
	}

	void pop() {
		if (!--count.front()) {
			count.pop_front();
			que.pop_front();
		}
	}

	const_reference min() const {
		return que.front();
	}
};

}

#endif // ALICE_MONOTONE_QUEUE_HPP
