#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft {
	template<typename InIt, typename OutIt>
	OutIt copy(InIt first, InIt last, OutIt X) {
		for (; first != last; ++X) {
			*X = *++first;
		}
		return X;
	}

	template<typename BidIt, typename OutIt> inline
	OutIt reverse_copy(BidIt first, BidIt last, OutIt X) {
		for (; first != last; ++X) {
			*X = *--last;
		}
		return X;
	}

	template<typename ForwardIt, typename T>
	void fill(ForwardIt first, ForwardIt last, const T &X)
	{
		for (; first != last; ++first) {
			*first = X;
		}
	}

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}
	
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class T>
	void swap (T& x, T& y) {
		T tmp = x;
		x = y;
		y = tmp;
	}
};

#endif