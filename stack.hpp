#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
	template<typename T, class C=ft::vector<T> > 
	class stack	{
		public:

			typedef C						container_type;
			typedef typename C::value_type	value_type;
			typedef typename C::size_type	size_type;

		protected:
			container_type cont;

		public:
			explicit stack(const container_type &layer = container_type()) : cont(layer) {}

			virtual ~stack() {}

			bool empty(void) const { return cont.empty(); }

			size_type size(void) const { return cont.size(); }

			value_type top(void) { return cont.back(); }

			const value_type top(void) const { return cont.back(); }

			void push(const value_type& val) { cont.push_back(val); }

			void pop(void) { cont.pop_back(); }

			bool Eq(const stack<T, C> &X) const { return (cont == X.cont); }

			bool Lt(const stack<T, C> &X) const	{ return (cont < X.cont); }	
			
	};

	template<class T, class C>
		bool operator==(const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.Eq(rhs); }

	template<class T, class C>
		bool operator!=(const stack<T, C>& lhs, const stack<T, C>& rhs) { return !(lhs == rhs); }

	template<class T, class C>
		bool operator<(const stack<T, C>& lhs, const stack<T, C>& rhs) { return lhs.Lt(rhs); }

	template<class T, class C>
		bool operator<=(const stack<T, C>& lhs, const stack<T, C>& rhs) { return !(lhs > rhs); }

	template<class T, class C>
		bool operator>(const stack<T, C>& lhs, const stack<T, C>& rhs) { return rhs < lhs; }
	
	template<class T, class C>
		bool operator>=(const stack<T, C>& lhs, const stack<T, C>& rhs) { return !(lhs < rhs); }
}

#endif