#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "../common/utility.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct Int_iterator_tag {};

	template <typename C, typename T, typename Dist = std::ptrdiff_t, typename Pt = T*, typename Rt = T&>
	struct iterator {
		typedef C		iterator_category;
		typedef T		value_type;
		typedef Dist	difference_type;
		typedef Pt		pointer;
		typedef Rt		reference;
	};

	template<typename T, typename D, typename Pt, typename Rt>
	struct BidIt : public iterator<ft::bidirectional_iterator_tag, T, D, Pt, Rt> {};

	template<typename T, typename D, typename Pt, typename Rt>
	struct RanIt : public iterator<ft::random_access_iterator_tag, T, D, Pt, Rt> {};

	struct OutIt : public iterator<ft::output_iterator_tag, void, void, void, void> {};

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
		typedef ft::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef ft::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
	};

	// * === ITER_CAT === * //

	template <typename C, typename T, typename D, typename Pt, typename Rt> inline
	C Iter_cat(const iterator<C, T, D, Pt, Rt>&) {
		C X;
		return X;
	}

	template<typename T> inline
	ft::random_access_iterator_tag Iter_cat(const T*) {
		ft::random_access_iterator_tag X;
		return X;
	}

	inline ft::Int_iterator_tag Iter_cat(bool) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(char) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(signed char) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(unsigned char) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(wchar_t) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(short) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(unsigned short) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(int) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(unsigned int) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(long) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	inline ft::Int_iterator_tag Iter_cat(unsigned long) { 
		ft::Int_iterator_tag X; 
		return X; 
	}

	template <typename InIter, typename D, typename IterCategory>
	void	my_distance_helper(InIter first, InIter last, D& dist, ft::input_iterator_tag) {
		for(; first != last; ++first)
			++dist;
	}

	template <typename RanIt, typename D>
	void	my_distance_helper(RanIt first, RanIt last, D& dist, ft::random_access_iterator_tag) {
		dist += last - first;
	}

	template <typename InIter>
	typename ft::iterator_traits<InIter>::difference_type distance (InIter first, InIter last) {
		typename ft::iterator_traits<InIter>::difference_type dist = 0;
		my_distance_helper(first, last, dist, Iter_cat(first));
		return dist;
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