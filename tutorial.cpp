#include <memory>
#include <iostream>
#include <set>
#include <vector>

// 1. InputIterator -->  / *it, ++, == /  You can only iterate over collection once
// 2. ForwardIterator --> InputIterator with multiple iteration guarantee --> forward_list::iterator  unordered_map::iterator
// 3. BidirectionalIterator --> / -- / --> list::iterator   set::iterator  map::iterator  Not linear positioning of elements
// 4. RandomAccessItertor -->  / < > <= >= +=n -=n it2 - it1 / --> vector::iterator   deque::iterator
// 5. ContiguousIterator(Since C++17) -> &(*it) + 1 --> linear positioning of elements --> vector, array, C-style pointers

// template<typename T>
// struct iterator_traits {
// 	using value_type = ...;
// 	using iterator_category = ...;
// }

// struct input_iterator_tag {};
// struct forward_iterator_tag : public input_iterator_tag {};

template<typename Iterator, typename IterCategory>
void my_advance_helper(Iterator& iter, IterCategory, int n) {
	for (int i = 0; i < n; ++i) {
		++iter;
	}
}

template<typename Iterator>
void my_advance_helper(Iterator& iter, std::random_access_iterator_tag, int n) {
	iter += n;
}

template<typename Iterator>
void my_advance(Iterator& iter, int n) {
	my_advance_helper(iter, typename std::iterator_traits<Iterator>::iterator_category(), n);
}

int main() {
	std::set<int> s;
	for (int i = 0; i < 100; ++i) {
		s.insert(i);
	}
	std::set<int>::iterator it = s.begin();
	my_advance(it, 25);
	std::cout << *it;
	my_advance(it, -10);
	std::cout << *it;
}