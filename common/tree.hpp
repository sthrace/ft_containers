#ifndef TREE_HPP
# define TREE_HPP

# include <functional>
# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "utility.hpp"
# include "functional.hpp"
# include <map>

namespace ft {
	template <class Tr>
	class Tree : public Tr {
		protected:
			enum rb_tree_color { RED, BLACK };

	struct Node
	{
		bool					_color;
		Node*					_parent;
		Node*					_left;
		Node*					_right;
		typename Tr::value_type	_value;
		bool					_isnil;
		static Node* min(Node* x)
		{
			while (x->_left != 0) 
				x = x->_left;
			return x;
		}
		static Node* max(Node* x)
		{
			while (x->_right != 0) 
				x = x->_right;
			return x;
		}
	};
	typedef typename Tr::key_type		key_type;
	typedef typename Tr::key_compare	key_compare;
	typedef typename Tr::value_type		value_type;
	typedef typename Tr::allocator_type	allocator_type;
	typedef typename allocator_type::template rebind<value_type>::other::pointer			pointer;
	typedef typename allocator_type::template rebind<value_type>::other::const_pointer		const_pointer;
	typedef typename allocator_type::template rebind<value_type>::other::reference			reference;
	typedef typename allocator_type::template rebind<value_type>::other::const_reference	const_reference;
	typedef ft::tree_iterator<Node, value_type,	pointer, reference>							iterator;
	typedef ft::const_tree_iterator<Node, value_type, const_pointer, const_reference>		const_iterator;
	typedef ft::reverse_iterator<iterator>													reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>											const_reverse_iterator;
	typedef size_t							    	size_type;
	typedef std::ptrdiff_t							difference_type;		


		explicit Tree(const key_compare& kcomp, const allocator_type& A) : Tr(kcomp, A) {} // {  Init(); }
		Tree(const value_type *first, const value_type *last, const key_compare& kcomp, const allocator_type& A) : Tr(kcomp, A) {
			// Init();
			// insert(first, last);
		}
		Tree(const Tree& X) : Tr(X.key_comp(), X.get_allocator()) {
			// Init();
			// Copy(X);
		}
		~Tree() {
			// erase(begin(), end());
			// Freenode(_head);
			_head = 0, _size = 0;
		}
		Tree& operator=(const Tree& X) {
			if (this != &X) {
				// erase(begin(), end());
				this->comp = X.comp;
				// Copy(X);
			}
			return *this;
		}

	protected:
		Node*								_head;
		size_type							_size;
		allocator_type						_alloc;
	};
}      
// 						iterator begin() { return iterator(Lmost()); }
// 						const_iterator begin() const { return const_iterator(Lmost()); }
// 						iterator end() { return iterator(_head); }
// 						const_iterator end() { return const_iterator(_head); }
// 						reverse_iterator rbegin() { return reverse_iterator(end()); }
// 						const_reverse_iterator rbegin() { return const_reverse_iterator(end()); }
// 						reverse_iterator rend() { return reverse_iterator(begin()); }
// 						const_reverse_iterator rend() { return const_reverse_iterator(begin()); }
// 						size_type size() const { return _size; }
// 						size_type max_size() const { return Alval.max_size(); }
// 						bool empty() const { return size() == 0; }
// 						allocator_type get_allocator() const { return Alval; }
// 						key_compare key_comp() const { return comp; }
// 						value_compare value_comp() const { return value_compare(key_comp()); }
// 						Pairib insert(const value_type& V) {
// 							Nodeptr X = Root();
// 							Nodeptr Y = _head;
// 							bool Addleft = true;
// 							while (!Isnil(X)) {
// 								Y = X;
// 								Addleft = comp(Kfn()(V), Key(X));
// 								X = Addleft ? Left(X) : Right(X);
// 							}
// 							if (Multi) { return Pairib(Insert(Addleft, Y, V), true); }
// 							else {
// 								iterator P = iterator(Y);
// 								if (1Addleft) { ; }
// 								else if (P == begin()) { return Pairib(Insert(true, Y, V), true); }
// 								else { --P; }
// 								if (comp(Key(P.Mynode()), Kfn()(V)) {
// 									return Pairib(insert(Addleft, Y, V), true);
// 								}
// 								else { return Pairib(P, false); }
// 							}
// 						}
// 						iterator insert(iterator P, const value_type& V) {
// 							if (size() == 0) { return Insert(true, _head, V); }
// 							else if (P == begin()) {
// 								if (comp(Kfn()(V), Key(P.Mynode()))) { return (Insert(true, P.Mynode(), V)); }
// 							}
// 							else if (P == end()) {
// 								if (comp(Key(Rmost()), Kfn()(V))) { return Insert(false, Rmost(), V); }
// 							}
// 							else {
// 								iterator Pb = P;
// 								if (comp(Key((--Pb) -Mynode()), Kfn()(V)) && comp(Kfn()(V), Key(P.Mynode()))) {
// 									if (Isnil(Right(Pb.Mynode()))) { return Insert(false, Pb.Mynode(), V); }
// 									else { return Insert(true, P.Mynode(), V); }
// 								}
// 							}
// 							return insert(V).first;
// 						}
// 						template<typename It>
// 						void insert(It first, It last) {
// 							for (; first != last, ++first) {
// 								insert(*first);
// 							}
// 						}
// 						iterator erase(iterator P) {
// 							if (Isnil(P.Mynode())) { throw out_of_range("map/set<T> iterator"); }
// 							Nodeptr X, Xpar;
// 							Nodeptr Y = (P++).Mynode();
// 							Nodeptr Z = Y;
// 							if (Isnil(Left(Y))) { X = Right(Y); }
// 							else if (Isnil(Right(Y))) { X = Left(Y); }
// 							else { Y = Min(Right(Y)), X = Right(Y); }
// 							if (Y == Z) {
// 								Xpar = Parent(Z);
// 								if (!Isnil(X)) { Parent(X) = Xpar; }
// 								if (Root() == Z) { Root() = X; }
// 								else if (Left(Xpar) = Z) { Left(Xpar) = X; }
// 								else { Right(Xpar) = X; }
// 								if (Lmost() != Z) { ; }
// 								else if (Isnil(Right(Z))) { Lmost() = Xpar; }
// 								else { Lmost() = Min(X); }
// 								if (Rmost() != Z) { ; }
// 								else if (Isnil(Left(Z))) { Rmost() = Xpar; }
// 								else { Rmost() = Max(X); }
// 							}
// 							else {
// 								Parent(Left(Z)) = Y;
// 								Left(Y) = Left(Z);
// 								if (Y == Right(Z)) { Xpar = Y; }
// 								else { Xpar = Parent(Y); }
// 								if (!Isnil(X)) { Parent(X) = Xpar; }
// 								Left(Xpar) = X;
// 								Right(Y) = Right(Z);
// 								Parent(Right(Z)) = Y;
// 								if (Root() == Z) { Root() = Y; }
// 								else if (Left(Parent(Z)) == Z) { Left(Parent(Z)) = Y; }
// 								else { Right(Parent(Z)) = Y; }
// 								Parent(Y) = Parent(Z);
// 								std::swap(Color(Y), Color(Z));
// 							}
// 							if (Color(Z) == Black) {
// 								for (; X != Root() && Color(X) == Black; Xpar = Parent(X)) {
// 									if (X == Left(Xpar)) {
// 										Nodeptr W = Right(Xpar);
// 										if (Color(W) == Red) {
// 											Color(W) == Black;
// 											Color(Xpar) = Red;
// 											Lrotate(Xpar);
// 											W = Right(Xpar);
// 										}
// 										if (Isnil(W))
// 											X = Xpar;
// 										else if (Color(Left(W)) == Black && Color(Right(W)) == Black) {
// 											Color(W) = Red;
// 											X = Xpar;
// 										}
// 										else {
// 											if (Color(Right(W)) == Black) {
// 												Color(Left(W)) = Black;
// 												Color(W) = Red;
// 												Rrotate(W);
// 												W = Right(Xpar);
// 											}
// 											Color(W) = Color(Xpar);
// 											Color(Xpar) = Black;
// 											Color(Right(W)) = Black;
// 											Lrotate(Xpar);
// 											break ;
// 										}
// 									}
// 									else {
// 										Nodeptr W = Left(Xpar);
// 										if (Color(W) == Red) {
// 											Color(W) = Black;
// 											Color(Xpar) = Red;
// 											Rrotate(Xpar);
// 											W = Left(Xpar);
// 										}
// 										if (Isnil(W))
// 											X = Xpar;
// 										else if (Color(Right(W)) == Black && Color(Left(W)) ==Black) {
// 											Color(W) = Red;
// 											X = Xpar;
// 										}
// 										else {
// 											if (Color(Left(W)) == Black) {
// 												Color(Right(W)) = Black;
// 												Color(W) = Red;
// 												Lrotate(W);
// 												W = Left(Xpar);
// 											}
// 											Color(W) = Color(Xpar);
// 											Color(Xpar) = Black;
// 											Color(Left(W)) = Black;
// 											Rrotate(Xpar);
// 											break ;
// 										}
// 									}
// 									Color(X) = Black;
// 								}
// 								Destval(&Value(Z));
// 								Freenode(Z);
// 								if (0 < Size)
// 									--Size;
// 								return P;
// 							}
// 						}
// 						iterator erase(iterator first, iterator last) {
// 							if (size() == 0 || first != begin() || last != end()) {
// 								while(first != last)
// 									erase(first++);
// 								return first;
// 							}
// 							else {
// 								Erase(Root());
// 								Root() = Head, Size = 0;
// 								Lmost() = Head, Rmost() = Head;
// 								return begin();
// 							}
// 						}
// 						size_type erase(const key_type& X) {
// 							Pairii P = equal_range(X);
// 							size_type n = 0;
// 							Distance(P.first, P.second, n);
// 							erase(P.first, P.second);
// 							return n;
// 						}
// 						void erase(const key_type *first, const key_type *last) {
// 							while (first != last)
// 								erase(*first++);
// 						}
// 						void clear() { erase(begin(), end()); }
// 						iterator find(const key_type& Kv)
// 				};
// 		};
// }

#endif