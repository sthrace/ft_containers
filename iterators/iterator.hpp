#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "../common/utility.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <typename C, typename T, typename Dist = std::ptrdiff_t, typename Pt = T*, typename Rt = T&>
	struct iterator {
		typedef C		iterator_category;
		typedef T		value_type;
		typedef Dist	difference_type;
		typedef Pt		pointer;
		typedef Rt		reference;
	};

	template<typename T, typename D, typename Pt, typename Rt>
	struct BidIt : public iterator<bidirectional_iterator_tag, T, D, Pt, Rt> {};

	template<typename T, typename D, typename Pt, typename Rt>
	struct RanIt : public iterator<random_access_iterator_tag, T, D, Pt, Rt> {};

	struct OutIt : public iterator<output_iterator_tag, void, void, void, void> {};

	template <typename Iter>
	struct iterator_traits {
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag			iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
	};

	template <typename C, typename T, typename D, typename Pt, typename Rt>
	C iterator_category(const iterator<C, T, D, Pt, Rt>&) {
		C X;
		return X;
	}

	template<typename T>
	input_iterator_tag iterator_category(const T*) {
		input_iterator_tag X;
		return X;
	}

	template<typename T>
	output_iterator_tag iterator_category(const T*) {
		output_iterator_tag X;
		return X;
	}

	template<typename T>
	forward_iterator_tag iterator_category(const T*) {
		forward_iterator_tag X;
		return X;
	}

	template<typename T>
	bidirectional_iterator_tag iterator_category(const T*) {
		bidirectional_iterator_tag X;
		return X;
	}

	template<typename T>
	random_access_iterator_tag iterator_category(const T*) {
		random_access_iterator_tag X;
		return X;
	}

	template <typename Iter, typename D>
	void	my_distance_helper(Iter first, Iter last, D& dist, input_iterator_tag) {
		for(; first != last; ++first)
			++dist;
	}

	template <typename Iter, typename D>
	void	my_distance_helper(Iter first, Iter last, D& dist, random_access_iterator_tag) {
		dist += last - first;
	}

	template <typename Iter>
	typename ft::iterator_traits<Iter>::difference_type distance (Iter first, Iter last) {
		typename ft::iterator_traits<Iter>::difference_type dist = 0;
		my_distance_helper(first, last, dist, ft::iterator_category(first));
		return dist;
	}

	template<typename Iter, typename IterCategory>
	void my_advance_helper(Iter& iter, IterCategory, int n) {
		for (int i = 0; i < n; ++i) {
			++iter;
		}
	}

	template<typename Iter>
	void my_advance_helper(Iter& iter, bidirectional_iterator_tag, int n) {
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

	template<typename Iter>
	void my_advance_helper(Iter& iter, random_access_iterator_tag, int n) {
		iter += n;
	}

	template<typename Iter>
	void advance(Iter& iter, int n) {
		my_advance_helper(iter, typename iterator_traits<Iter>::iterator_category(), n);
	}
}

#endif