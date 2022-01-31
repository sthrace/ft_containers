#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft {
	template <class T1, class T2> struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		// * === CONSTRUCTORS === * //

		pair() : first(T1()), second(T2()) {}
		pair(const T1& V1, const T2& V2) : first(V1), second(V2) {}
		template <class U1, class U2>
			pair(const pair<U1, U2>& X) : first(X.first), second(X.second) {}
		~pair() {}

		pair& operator=(const pair& X) {
			if (this != &X) {
				first = X.first;
				second = X.second;
			}
			return *this;
		}
		T1 first;
		T2 second;
	};

	template<class T1, class T2> inline
	bool operator==(const ft::pair<T1, T2>& X, const ft::pair<T1, T2>& Y) {
		return (X.first == Y.first && X.second == Y.second);
	}
	template<class T1, class T2> inline
	bool operator!=(const ft::pair<T1, T2>& X, const ft::pair<T1, T2>& Y) {
		return !(X == Y);
	}
	template<class T1, class T2> inline
	bool operator<(const ft::pair<T1, T2>& X, const ft::pair<T1, T2>& Y) {
		return (X.first < Y.first || (!(Y.first < X.first) && X.second < Y.second));
	}
	template<class T1, class T2> inline
	bool operator>(const ft::pair<T1, T2>& X, const ft::pair<T1, T2>& Y) {
		return Y < X;
	}
	template<class T1, class T2> inline
	bool operator<=(const ft::pair<T1, T2>& X, const ft::pair<T1, T2>& Y) {
		return !(Y < X);
	}
	template<class T1, class T2> inline
	bool operator>=(const ft::pair<T1, T2>& X, const ft::pair<T1, T2>& Y) {
		return !(X < Y);
	}
	template<class T1, class T2> inline
	ft::pair<T1, T2> make_pair(const T1& X, const T2& Y) {
		return ft::pair<T1, T2>(X, Y);
	}
};

#endif