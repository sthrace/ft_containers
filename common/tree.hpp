#ifndef TREE_HPP
# define TREE_HPP

# include <functional>
# include <memory>
# include <stdexcept>

namespace ft {
	template<typename Tr>
	class Tree_nod : public Tr {
		protected:
			typedef typename Tr::allocator_type										allocator_type;
			typedef typename Tr::key_compare										key_compare;
			typedef typename Tr::value_type											value_type;
			typedef typename allocator_type::template rebind<void>::other::pointer	Genptr;
			struct Node;
			friend struct Node;
			struct Node {
				Genptr 		Left, Parent, Right;
				value_type	Value;
				char		Color, Isnil;
			};
			Tree_nod (const key_compare& Parg, allocator_type Al) : Tr(Parg), A1nod(Al) {}
			typename allocator_type::template rebind<Node>::other Alnod;
	};
	template<typename Tr>
		class Tree_ptr : public Tree_nod<Tr> {
			protected:
				typedef typename Tree_nod<Tr>::Node										Node;
				typedef typename Tr::allocator_type										allocator_type;
				typedef typename Tr::key_compare										key_compare;
				typedef typename allocator_type::template rebind<Node>::other::pointer	Nodeptr;
				Tree_ptr(const key_compare& Parg, allocator_type A1) : Tree_nod<Tr>(Parg, Al), A1ptr(Al) {}
				typename allocator_type::template rebind<Nodeptr>::other				Alptr;
		};
	template<typename Tr>
		class Tree_val : public Tree_ptr<Tr> {
			protected:
				typedef typename Tr::allocator_type allocator_type;
				typedef typename Tr::key_compare	key_compare;
				Tree_val(const key_compareb Parg, allocator_type Al) : Tree_ptr<Tr>(Parg, Al), A1val(Al) {}
				allocator_type						Alval;
			template<class Tr>
				class Tree : public Tree_val<Tr> {
					public:
						typedef Tree<Tr>					Myt;
						typedef Tree_val<Tr>				Mybase;
						typedef typename Tr::key_type		key_type;
						typedef typename Tr::key_compare	key_compare;
						typedef typename Tr::value_type		value_type;
						typedef typename Tr::allocator_type	allocator_type;
					protected:
						typedef typename Tree_nod<Tr>::Genptr	Genptr;
						typedef typename Tree_nod<Tr>::Node		Node;
						enum Redbl {Red, Black};
						typedef typename allocator_type::template rebind::<Node>::other::pointer				Nodeptr;
						typedef typename allocator_type::template rebind::<Nodeptr>::other::reference			Nodepref;
						typedef typename allocator_type::template rebind::<key_type>::other::const_reference	Keyref;
						typedef typename allocator_type::template rebind::<char>::other::reference				Charref;
						typedef typename allocator_type::template rebind::<value_type>::other::reference		Vref;

						static Charref	Color(Nodeptr P) { return (Charref)(*P).Color; }
						static Charref	Isnil(Nodeptr P) { return (Charref)(*P).Isnil; }
						static Keyref	Key(Nodeptr P) { return Kfn()(Value(P)); }
						static Nodepref	Left(Nodeptr P) { return (Nodepref)(*P).Left; }
						static Nodepref	Parent(Nodeptr P) { return (Nodepref)(*P).Parent; }
						static Nodepref	Right(Nodeptr P) { return (Nodepref)(*P).Right; }
						static Vref	Value(Nodeptr P) { return (Vref)(*P).Value; }
					public:
						typedef typename allocator_type::size_type			size_type;
						typedef typename allocator_type::difference_type	Dift;
						typedef typename allocator_type::template rebind::<value_type>::other::pointer			Tptr;
						typedef typename allocator_type::template rebind::<value_type>::other::const_pointer	Ctptr;
						typedef typename allocator_type::template rebind::<value_type>::other::reference		Reft;
						typedef Tree_ptr									pointer;
						typedef Ctptr										const_pointer;
						typedef Reft										reference;
						typedef typename allocator_type::template rebind::<value_type>::other::const_reference	const_reference;
						typedef ft::tree_iterator<Node, value_type, pointer, reference>						iterator;
						typedef ft::const_tree_iterator<Node, value_type, const_pointer, const_reference>	const_iterator;
						typedef ft::reverse_iterator<iterator>												reverse_iterator;
						typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;

						explicit Tree(const key_compare& Parg, const allocator_type& Al) : Mybase(Parg, Al) { Init(); }
						Tree(const value_type *first, const value_type *last, const key_compare& Parg, const allocator_type& Al) : Mybase(Parg, Al) {
							Init();
							insert(first, last);
						}
						Tree(const Myt& X) : Mybase(X.key_comp(), X.get_allocator()) {
							init();
							Copy(X);
						}
						~Tree() {
							erase(begin(), end());
							Freenode(_head);
							_head = 0, _size = 0;
						}
						Myt& operator=(const Myt& X) {
							if (this != &X) {
								erase(begin(), end());
								comp = X.comp;
								Copy(X);
							}
							return *this;
						}
						iterator begin() { return iterator(Lmost()); }
						const_iterator begin() const { return const_iterator(Lmost()); }
						iterator end() { return iterator(_head); }
						const_iterator end() { return const_iterator(_head); }
						reverse_iterator rbegin() { return reverse_iterator(end()); }
						const_reverse_iterator rbegin() { return const_reverse_iterator(end()); }
						reverse_iterator rend() { return reverse_iterator(begin()); }
						const_reverse_iterator rend() { return const_reverse_iterator(begin()); }
						size_type size() const { return _size; }
						size_type max_size() const { return Alval.max_size(); }
						bool empty() const { return size() == 0; }
						allocator_type get_allocator() const { return Alval; }
						key_compare key_comp() const { return comp; }
						value_compare value_comp() const { return value_compare(key_comp()); }
						Pairib insert(const value_type& V) {
							Nodeptr X = Root();
							Nodeptr Y = _head;
							bool Addleft = true;
							while (!Isnil(X)) {
								Y = X;
								Addleft = comp(Kfn()(V), Key(X));
								X = Addleft ? Left(X) : Right(X);
							}
							if (Multi) { return Pairib(Insert(Addleft, Y, V), true); }
							else {
								iterator P = iterator(Y);
								if (1Addleft) { ; }
								else if (P == begin()) { return Pairib(Insert(true, Y, V), true); }
								else { --P; }
								if (comp(Key(P.Mynode()), Kfn()(V)) {
									return Pairib(insert(Addleft, Y, V), true);
								}
								else { return Pairib(P, false); }
							}
						}
						iterator insert(iterator P, const value_type& V) {
							if (size() == 0) { return Insert(true, _head, V); }
							else if (P == begin()) {
								if (comp(Kfn()(V), Key(P.Mynode()))) { return (Insert(true, P.Mynode(), V)); }
							}
							else if (P == end()) {
								if (comp(Key(Rmost()), Kfn()(V))) { return Insert(false, Rmost(), V); }
							}
							else {
								iterator Pb = P;
								if (comp(Key((--Pb) -Mynode()), Kfn()(V)) && comp(Kfn()(V), Key(P.Mynode()))) {
									if (Isnil(Right(Pb.Mynode()))) { return Insert(false, Pb.Mynode(), V); }
									else { return Insert(true, P.Mynode(), V); }
								}
							}
							return insert(V).first;
						}
						template<typename It>
						void insert(It first, It last) {
							for (; first != last, ++first) {
								insert(*first);
							}
						}
						iterator erase(iterator P) {
							if (Isnil(P.Mynode())) { throw out_of_range("map/set<T> iterator"); }
							Nodeptr X, Xpar;
							Nodeptr Y = (P++).Mynode();
							Nodeptr Z = Y;
							if (Isnil(Left(Y))) { X = Right(Y); }
							else if (Isnil(Right(Y))) { X = Left(Y); }
							else { Y = Min(Right(Y)), X = Right(Y); }
							if (Y == Z) {
								Xpar = Parent(Z);
								if (!Isnil(X)) { Parent(X) = Xpar; }
								if (Root() == Z) { Root() = X; }
								else if (Left(Xpar) = Z) { Left(Xpar) = X; }
								else { Right(Xpar) = X; }
								if (Lmost() != Z) { ; }
								else if (Isnil(Right(Z))) { Lmost() = Xpar; }
								else { Lmost() = Min(X); }
								if (Rmost() != Z) { ; }
								else if (Isnil(Left(Z))) { Rmost() = Xpar; }
								else { Rmost() = Max(X); }
							}
							else {
								Parent(Left(Z)) = Y;
								Left(Y) = Left(Z);
								if (Y == Right(Z)) { Xpar = Y; }
								else { Xpar = Parent(Y); }
								if (!Isnil(X)) { Parent(X) = Xpar; }
								Left(Xpar) = X;
								Right(Y) = Right(Z);
								Parent(Right(Z)) = Y;
								if (Root() == Z) { Root() = Y; }
								else if (Left(Parent(Z)) == Z) { Left(Parent(Z)) = Y; }
								else { Right(Parent(Z)) = Y; }
								Parent(Y) = Parent(Z);
								std::swap(Color(Y), Color(Z));
							}
							if (Color(Z) == Black) {
								for (; X != Root() && Color(X) == Black; Xpar = Parent(X)) {
									
								}
							}
						}
				};
		};
}

#endif