#ifndef SET_HPP
# define SET_HPP

# include "../common/tree.hpp"

namespace ft {
	template <class K, class Pr, class A, bool Mfl>
	class Tset_traits {
	public:
		typedef K	key_type;
		typedef K	value_type;
		typedef Pr	key_compare;
		typedef typename A::template rebind<value_type>::other allocator_type;
		Tset_traits() : comp() {}
		Tset_traits(Pr Parg) : comp(Parg) {}
		typedef key_compare	value_compare;
		const K& operator()(const value_type& X) const { return X; }
	protected:
		const key_type& getKeyByVal(const value_type& val) const {
			return val;
		}
		Pr comp;
	};

	template <class K, class Pr = ft::less<K>, class A = std::allocator<K> >
	class set : public ft::Tree<Tset_traits<K, Pr, A, false> > {
	public:
		typedef Tree<Tset_traits<K, Pr, A, false> >		Mybase;
		typedef K										key_type;
		typedef Pr 										key_compare;
		typedef key_compare								value_compare;
		typedef typename Mybase::allocator_type			allocator_type;
		typedef typename Mybase::iterator				iterator;
		typedef typename Mybase::const_iterator			const_iterator;
		typedef typename Mybase::reverse_iterator		reverse_iterator;
		typedef typename Mybase::const_reverse_iterator	const_reverse_iterator;
		typedef typename Mybase::value_type				value_type;
		
		explicit set(const key_compare& comp = key_compare()) : Mybase(comp, allocator_type()) {}
		
		template <class It>
		set(It first, It last) : Mybase(key_compare(), allocator_type()) {
			for (; first != last; ++first)
				this->insert(*first);
		}

		template <class It>
		set(It first, It last, const key_compare& comp) : Mybase(comp, allocator_type()) {
			for (; first != last; ++first)
				this->insert(*first);
		}
		set(const set& X) : Mybase(X.comp, X._alloc_val) { 
				this->insert(X.begin(), X.end()); 
		}

		virtual ~set() {}
	};
};

#endif