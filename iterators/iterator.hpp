#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

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

	template<typename T>
	struct iterator_traits<T*> {
		typedef ft::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template<typename T>
	struct iterator_traits<const T*> {
		typedef ft::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
	};


	template <typename InIter, typename D>
	void	my_distance_helper(InIter first, InIter last, D& N, ft::input_iterator_tag) {
		for(; first != last; ++first)
			++N;
	}

	template <typename RanIt, typename D>
	void	my_distance_helper(RanIt first, RanIt last, D& N, ft::random_access_iterator_tag) {
		N += last - first;
	}

	template <typename InIter>
	typename ft::iterator_traits<InIter>::difference_type distance (InIter first, InIter last) {
		typename ft::iterator_traits<InIter>::difference_type N = 0;
		my_distance_helper(first, last, N, typename ft::iterator_traits<InIter>::iterator_category());
		return N;
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