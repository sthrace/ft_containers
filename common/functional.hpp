#ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft {
	template <class A1, class A2, class R>
	struct binary_function {
		typedef A1 first_argument_type;
		typedef A2 second_argument_type;
		typedef R result_type;
	};
	
	template <class T>
	struct less : binary_function<T, T, bool> {
		bool operator()(const T& X, const T& Y) const { return X < Y; }
	};
}

#endif