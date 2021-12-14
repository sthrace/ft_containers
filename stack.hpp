#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <vector>

namespace ft {
	template<typename T, class C=std::vector<T> > 
	class stack	{
		public:
			typedef C						container_type;
			typedef typename C::value_type	value_type;
			typedef typename C::size_type	size_type;

			explicit stack(const C &Cont) : c(Cont) {}
			stack(void) : c() {}

			bool empty(void) const { return c.empty(); }
			size_type size(void) const { return c.size(); }
			value_type &top(void) { return c.back(); }
			const value_type &top(void) const { return c.back(); }
			void push(const value_type& X) { c.push_back(X); }
			void pop(void) { c.pop_back(); }
			bool Eq(const stack<T, C> &X) const { return (c == X.c); }
			bool Lt(const stack<T, C> &X) const	{ return (c < X.c); }	

		protected:
			C c;
	};

	template<class T, class C> inline
		bool operator==(const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.Eq(rhs); }
	template<class T, class C> inline
		bool operator!=(const stack<T, C>& lhs, const stack<T, C>& rhs) { return !(lhs == rhs); }
	template<class T, class C> inline
		bool operator<(const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.Lt(rhs); }
	template<class T, class C> inline
		bool operator>(const stack<T, C>& lhs, const stack<T, C>& rhs) { return rhs < lhs; }	
	template<class T, class C> inline
		bool operator<=(const stack<T, C>& lhs, const stack<T, C>& rhs) { return !(rhs < lhs); }
	template<class T, class C> inline
		bool operator>=(const stack<T, C>& lhs, const stack<T, C>& rhs) { return !(lhs < rhs); }
}

#endif