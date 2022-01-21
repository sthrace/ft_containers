#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <memory>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <typename C, typename T, typename Dist = std::ptrdiff_t, typename Pt = T*, typename Rt = T&>
	struct iterator {
		typedef C		iterator_category;
		typedef T		value_type;
		typedef Dist	difference_type;
		typedef Pt		pointer;
		typedef Rt		reference;
	};

	template<typename Iter>
	struct iterator_traits {
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template <typename InIter, typename Distance>
	void	my_distancehelper(InIter first, InIter last, Distance& result, ft::input_iterator_tag) {
		for(; first != last; ++first)
			++result;
	}

	template <typename RanIt, typename Distance>
	void	my_distance_helper(RanIt first, RanIt last, Distance& result, ft::random_access_iterator_tag) {
		result = last - first;
	}

	template <typename InIter>
	typename ft::iterator_traits<InIter>::difference_type	distance (InIter first, InIter last) {
		typename ft::iterator_traits<InIter>::difference_type result = 0;
		my_distance_helper(first, last, result, typename ft::iterator_traits<InIter>::iterator_category());
		return result;
	}

	template<typename Iterator, typename IterCategory>
	void my_advance_helper(Iterator& iter, IterCategory, int n) {
		for (int i = 0; i < n; ++i) {
			++iter;
		}
	}

	template<typename Iterator>
	void my_advance_helper(Iterator& iter, ft::bidirectional_iterator_tag, int n) {
		if (n > 0) {
			while (n--) {
				++iter;
			}
		}
		else {
			while (n++) {
				--iter;
			}
		}
	}

	template<typename Iterator>
	void my_advance_helper(Iterator& iter, ft::random_access_iterator_tag, int n) {
		iter += n;
	}

	template<typename Iterator>
	void advance(Iterator& iter, int n) {
		my_advance_helper(iter, typename ft::iterator_traits<Iterator>::iterator_category(), n);
	}
}

#endif