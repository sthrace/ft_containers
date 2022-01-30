#ifndef MAP_HPP
# define MAP_HPP

# include <stdexcept>
# include "../common/tree.hpp"

namespace ft {
template<typename K, typename T, typename Pr, typename A, bool Mfl>
class Tmap_traits {
	public:
		typedef K												key_type;
		typedef ft::pair<const K, T>							value_type;
		typedef Pr												key_compare;
		typedef typename A::template rebind<value_type>::other	allocator_type;
		enum {Multi = Mfl};
		Tmap_traits() : comp() {}
		Tmap_traits(Pr Parg) : comp(Parg) {}
		class value_compare : public ft::binary_function<value_type, value_type, bool> {
			public:
				bool operator()(const value_type& X, const value_type& Y) const {
					return comp(X._first, Y._first);
				}
				value_compare(key_compare comp) : comp(comp) {}
			protected:
				key_compare	comp;
		};
		struct Kfn {
			const K& operator()(const value_type& X) const { return X.first; }
		};
		Pr comp;
	}; // class Tmap_traits
	template<class K, class T, class Pr = ft::less<K>, class A = std::allocator<ft::pair<const K, T> > >
	class map : public ft::Tree<Tmap_traits<K, T, Pr, A, false> > {
		public:
			typedef ft::Tree<Tmap_traits<K, T, Pr, A, false> >	Mybase;
			typedef K											key_type;
			typedef T											mapped_type;
			// typedef T											referent_type;
			typedef Pr											key_compare;
			// typedef typename Mybase::value_compare				value_compare;
			typedef typename Mybase::allocator_type				allocator_type;
			// typedef typename Mybase::size_type					size_type;
			// typedef typename Mybase::difference_type			difference_type;
			// typedef typename Mybase::pointer					pointer;
			// typedef typename Mybase::const_pointer				const_pointer;
			// typedef typename Mybase::reference					reference;
			// typedef typename Mybase::const_reference			const_reference;
			typedef typename Mybase::iterator					iterator;
			// typedef typename Mybase::const_iterator				const_iterator;
			// typedef typename Mybase::reverse_iterator			reverse_iterator;
			// typedef typename Mybase::const_reverse_iterator		const_reverse_iterator;
			typedef typename Mybase::value_type					value_type;

			explicit map(const key_compare& comp = key_compare()) : Mybase(comp, allocator_type()) {}

			template<class It>
			map(It first, It last) : Mybase(key_compare(), allocator_type()) {
				for (; first != last; ++first)
					insert(*first);
			}
			template<class It>
			map(It first, It last, const key_compare& comp) : Mybase(comp, allocator_type()) {
				for (; first != last; ++first)
					insert(*first);
			}
			mapped_type& operator[](const key_type& key) {
				iterator pos = insert(value_type(key, mapped_type())).first;
				return (*pos).second;
			}
	};
}; //namespace ft

#endif