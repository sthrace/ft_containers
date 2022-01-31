#ifndef MAP_HPP
# define MAP_HPP

# include "../common/tree.hpp"

namespace ft {
template <typename K, typename T, typename Pr, typename A, bool Mfl>
class Tmap_traits {
	public:
		typedef K												key_type;
		typedef ft::pair<const K, T>							value_type;
		typedef Pr												key_compare;
		typedef typename A::template rebind<value_type>::other	allocator_type;
		Tmap_traits() : comp() {}
		Tmap_traits(Pr c) : comp(c) {}
		class value_compare : public ft::binary_function<value_type, value_type, bool> {
			public:
				bool operator()(const value_type& X, const value_type& Y) const {
					return comp(X.first, Y.first);
				}
				value_compare(key_compare comp) : comp(comp) {}
			protected:
				key_compare	comp;
		};
		protected:
		const key_type& getKeyByVal(const value_type& pair) const {
			return pair.first;
		}
		key_compare comp;
	}; // class Tmap_traits

	template<class K, class T, class Pr = ft::less<K>, class A = std::allocator<ft::pair<const K, T> > >
	class map : public ft::Tree<Tmap_traits<K, T, Pr, A, false> > {
		public:
			typedef ft::Tree<Tmap_traits<K, T, Pr, A, false> >	Mybase;
			typedef K											key_type;
			typedef T											mapped_type;
			typedef Pr											key_compare;
			typedef typename Mybase::allocator_type				allocator_type;
			typedef typename Mybase::iterator					iterator;
			typedef typename Mybase::const_iterator				const_iterator;
			typedef typename Mybase::reverse_iterator			reverse_iterator;
			typedef typename Mybase::const_reverse_iterator		const_reverse_iterator;
			typedef typename Mybase::value_type					value_type;

			explicit map(const key_compare& comp = key_compare()) : Mybase(comp, allocator_type()) {}

			template<class It>
			map(It first, It last) : Mybase(key_compare(), allocator_type()) {
				for (; first != last; ++first) {
					this->insert(*first);
				}
			}

			template<class It>
			map(It first, It last, const key_compare& comp) : Mybase(comp, allocator_type()) {
				for (; first != last; ++first)
					this->insert(*first);
			}

			map(const map& X) : Mybase(X.comp, X._alloc_val) { 
				this->insert(X.begin(), X.end()); }
			
			mapped_type& operator[](const key_type& key) {
				iterator pos = this->insert(value_type(key, mapped_type())).first;
				return (*pos).second;
			}
	};
}; //namespace ft

#endif