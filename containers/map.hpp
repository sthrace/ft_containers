#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <limits>
# include <stdexcept>

namespace ft {
template<typename K, typename T, typename Pr, typename A, bool Mfl>
class Tmap_traits {
	public:
		typedef K												key_type;
		typedef pair<const K, T>								value_type;
		typedef Pr												key_compare;
		typedef typename A::template rebind<value_type>::other	allocator_type;
		enum {Multi = Mfl};
		Tmap_traits() : comp() {}
		Tmap_traits(Pr Parg) : comp(Parg) {}
		class value_compare : public binary function<value_type, value_type, bool> {
			friend class Tmap_traits<K, T, Pr, A, Mfl>;
			public:
				bool operator()(const value_type& X, const value_type& Y) const {
					return comp(X._first, Y._first);
				}
				value_compare(key_compare Pred) : comp(Pred) {}
			protected:
				key_compare	comp;
		};
		struct Kfn {
			const K& operator() (const value_type& X) const { return X._first }
		};
		Pr comp;
	}; // class Tmap_traits
	template<class K, class T, class Pr = less<K>, typename A = allocator<pair<const K, T> >
	class map : public ft::tree<Tmap_traits<K, T, Pr, A, false> > {
		public:
			typedef map<K, T, Pr, A>						Myt;
			typedef Tree<Tmap_traits<K, T, Pr, A, false> >	Mybase;
			typedef K										key_type;
			typedef T										mapped_type;
			typedef T										referent_type;
			typedef Pr										key_compare;
			typedef typename Mybase::value_compare			value_compare;
			typedef typename Mybase::allocator_type			allocator_type;
			typedef typename Mybase::size_type				size_type;
			typedef typename Mybase::difference_type		difference_type;
			typedef typename Mybase::pointer				pointer;
			typedef typename Mybase::const_pointer			const_pointer;
			typedef typename Mybase::reference				reference;
			typedef typename Mybase::const_reference		const_reference;
			typedef typename Mybase::iterator				iterator;
			typedef typename Mybase::const_iterator			const_iterator;
			typedef typename Mybase::reverse_iterator		reverse_iterator;
			typedef typename Mybase::const_reverse_iterator	const_reverse_iterator;
			typedef typename Mybase::value_type				value_type;

			map() : Mybase(key_compare(), allocator_type()) {}
			explicit map(const key_compare& Pred) : Mybase(Pred, allocator_type()) {}
			map(const key_compare& Pred, const allocator_type& A) : Mybase(Pred, A) {}
			template<class It>
			map(It first, It last) : Mybase(key_compare(), allocator_type()) {
				for (; first != last; ++first)
					insert(*first);
			}
			template<class It>
			map(It first, It last, const key_compare& Pred) : Mybase(Pred, allocator_type()) {
				for (; first != last; ++first)
					insert(*first);
			}
			template<class It>
			map(It first, It last, const key compare& Pred, const allocator_type& A) : Mybase(Pred, A) {
				for (; first != last; ++first)
					insert(*first);
			}
			mapped_type& operator[](const key_type& K) {
				iterator P = insert(value_type(K, mapped_type()))._first;
				return (*P)._second;
			}
	};
}; //namespace ft

#endif