#ifndef TREE_HPP
# define TREE_HPP

# include <functional>
# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "utility.hpp"
# include "functional.hpp"
# include "algorithm.hpp"

# include <iostream>

namespace ft {
	template <class Tr>
	class Tree : public Tr {
	protected:
		enum rb_tree_color { RED, BLACK };

		struct Node
		{
			char					_color;
			Node*					_parent;
			Node*					_left;
			Node*					_right;
			typename Tr::value_type	_value;
			bool					_isnil;
		};
		typedef typename Tr::key_type															key_type;
		typedef typename Tr::key_compare														key_compare;
		typedef typename Tr::value_type															value_type;
		typedef typename Tr::value_compare														value_compare;
		typedef typename Tr::allocator_type														allocator_type;
		typedef typename allocator_type::template rebind<Node>::other							allocator_node;
		typedef typename allocator_type::template rebind<Node *>::other							allocator_pointer;
		typedef typename allocator_type::template rebind<value_type>::other::pointer			pointer;
		typedef typename allocator_type::template rebind<value_type>::other::const_pointer		const_pointer;
		typedef typename allocator_type::template rebind<value_type>::other::reference			reference;
		typedef typename allocator_type::template rebind<value_type>::other::const_reference	const_reference;
		typedef ft::tree_iterator<Node, value_type,	pointer, reference>							iterator;
		typedef ft::const_tree_iterator<Node, value_type, const_pointer, const_reference>		const_iterator;
		typedef ft::reverse_iterator<iterator>													reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>											const_reverse_iterator;
		typedef size_t							    		size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef ft::pair<iterator, bool>					pair_ib;
		typedef ft::pair<iterator, iterator>				pair_ii;
		typedef ft::pair<const_iterator, const_iterator>	pair_cc;		

	public:
		Tree(const key_compare& comp, const allocator_type& A) : Tr(comp), _alloc_val(A), _alloc_node(A), _alloc_ptr(A) { Init(); }
		Tree(const value_type *first, const value_type *last, const key_compare& kcomp, const allocator_type& A) : Tr(kcomp, A) {
			Init();
			insert(first, last);
		}
		Tree(const Tree& X) : Tr(X.key_comp(), _alloc_val(X.get_allocator()), _alloc_node(X.get_allocator()), _alloc_ptr(X.get_allocator())) {
			Init();
			Copy(X);
		}
		virtual ~Tree() {
			erase(begin(), end());
			Freenode(_head);
			_head = 0, _size = 0;
		}
		Tree& operator=(const Tree& X) {
			if (this != &X) {
				erase(begin(), end());
				this->comp = X.comp;
				Copy(X);
			}
			return *this;
		}

		iterator begin() { return iterator(Lmost()); }
		const_iterator begin() const { return const_iterator(Lmost()); }
		iterator end() { return iterator(_head); }
		const_iterator end() const { return const_iterator(_head); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		size_type size() const { return _size; }
		size_type max_size() const { return _alloc_val.max_size(); }
		bool empty() const { return size() == 0; }
		allocator_type get_allocator() const { return _alloc_val; }
		key_compare key_comp() const { return this->comp; }
		value_compare value_comp() const { return value_compare(key_comp()); }

		pair_ib insert(const value_type& val) {
			Node* tmproot = Root();
			Node* tmphead = _head;
			bool Addleft = true;
			while(!tmproot->_isnil) {
				tmphead = tmproot;
				Addleft = this->comp(this->getKeyByVal(val), GetKey(tmproot));
				tmproot = Addleft ? tmproot->_left : tmproot->_right;
			}
			iterator pos = iterator(tmphead);
			if (!Addleft) { ; }
			else if (pos == begin())
				return pair_ib(Insert(true, tmphead, val), true);
			else
				--pos;
			if (this->comp(GetKey(pos.base()), this->getKeyByVal(val)))
				return pair_ib(Insert(Addleft, tmphead, val), true);
			else
				return pair_ib(pos, false);
		}

		iterator insert(iterator pos, const value_type& val) {
			if (size() == 0)
				return (Insert(true, _head, val));
			else if (pos == begin()) {
				if (this->comp(this->getKeyByVal(val), GetKey(pos.base())))
					return Insert(true, pos.base(), val);
			}
			else if (pos == end()) {
				if (this->comp(GetKey(Rmost()), this->getKeyByVal(val)))
					return Insert(false, Rmost(), val);
			}
			else {
				iterator it = pos;
				if (this->comp(GetKey((--it).base()), this->getKeyByVal(val)) && this->comp(this->getKeyByVal(val), GetKey(pos.base()))) {
					if (it.base()->_right->_isnil)
						return Insert(false, it.base(), val);
					else
						return Insert(true, pos.base(), val);
				}
			}
			return insert(val).first;
		}

		template <class It>
		void insert(It first, It last) {
			for (; first != last; ++first)
				insert(*first);
		}

		iterator erase(iterator pos) {
			if (pos.base()->_isnil)
				throw std::out_of_range("map/set<T> iterator");
			Node* X;
			Node* Xpar;
			Node* Y = (pos++).base();
			Node* Z = Y;
			if (Y->_left->_isnil)
				X = Y->_right;
			else if (Y->_right->_isnil)
				X = Y->_left;
			else
				Y = Min(Y->_right), X = Y->_right;
			if (Y == Z) {
				Xpar = Z->_parent;
				if (!X->_isnil)
					X->_parent = Xpar;
				if (Root() == Z)
					Root() = X;
				else if (Xpar->_left == Z)
					Xpar->_left = X;
				else
					Xpar->_right = X;
				if (Lmost() != Z) { ; }
				else if (Z->_right->_isnil)
					Lmost() = Xpar;
				else
					Lmost() = Min(X);
				if (Rmost() != Z) { ; }
				else if (Z->_left->_isnil)
					Rmost() = Xpar;
				else
					Rmost() = Max(X);
			}
			else {
				Z->_left->_parent = Y;
				Y->_left = Z->_left;
				if (Y == Z->_right)
					Xpar = Y;
				else {
					Xpar = Y->_parent;
					if (!X->_isnil)
						X->_parent = Xpar;
					Xpar->_left = X;
					Y->_right = Z->_right;
					Z->_right->_parent = Y;
				}
				if (Root() == Z)
					Root() = Y;
				else if (Z->_parent->_left == Z)
					Z->_parent->_left = Y;
				else
					Z->_parent->_right = Y;
				Y->_parent = Z->_parent;
				ft::swap(Y->_color, Z->_color);
			}
			if (Z->_color == BLACK) {
				for (; X != Root() && X->_color == BLACK; Xpar = X->_parent) {
					if (X == Xpar->_left) {
						Node* W = Xpar->_right;
						if (W->_color == RED) {
							W->_color = BLACK;
							Xpar->_color = RED;
							Lrotate(Xpar);
							W = Xpar->_right;
						}
						if (W->_isnil)
							X = Xpar;
						else if (W->_left->_color == BLACK && W->_right->_color == BLACK) {
							W->_color = RED;
							X = Xpar;
						}
						else {
							if (W->_right->_color == BLACK) {
								W->_left->_color = BLACK;
								W->_color = RED;
								Rrotate(W);
								W = Xpar->_right;
							}
							W->_color = Xpar->_color;
							Xpar->_color = BLACK;
							W->_right->_color = BLACK;
							Lrotate(Xpar);
							break ;
						}
					}
					else {
						Node* W = Xpar->_left;
						if (W->_color == RED) {
							W->_color = BLACK;
							Xpar->_color = RED;
							Rrotate(Xpar);
							W = Xpar->_left;
						}
						if (W->_isnil)
							X = Xpar;
						else if (W->_right->_color == BLACK && W->_left->_color == BLACK) {
							W->_color = RED;
							X = Xpar;
						}
						else {
							if (W->_left->_color == BLACK) {
								W->_right->_color = BLACK;
								W->_color = RED;
								Lrotate(W);
								W = Xpar->_left;
							}
							W->_color = Xpar->_color;
							Xpar->_color = BLACK;
							W->_left->_color = BLACK;
							Rrotate(Xpar);
							break ;
						}
					}
				}
				X->_color = BLACK;
			}
			Destroy_value(&Z->_value);
			Freenode(Z);
			if (0 < _size)
				--_size;
			return pos;
		}

		iterator erase(iterator first, iterator last) {
			if (size() == 0 || first != begin() || last != end()) {
				while(first != last)
					erase(first++);
				return first;
			}
			else {
				Erase(Root());
				Root() = _head;
				_size = 0;
				Lmost() = _head;
				Rmost() = _head;
				return begin();
			}
		}

		size_type erase(const key_type& key) {
			pair_ii pair = equal_range(key);
			size_type n = ft::distance(pair.first, pair.second);
			erase(pair.first, pair.second);
			return n;
		}

		void erase(const key_type *first, const key_type *last) {
			while (first != last)
				erase(*first++);
		}

		void clear() { erase(begin(), end()); }

		iterator find(const key_type& key) {
			iterator pos = lower_bound(key);
			return pos == end() || this->comp(key, GetKey(pos.base())) ? end() : pos;
		}

		const_iterator find(const key_type& key) const {
			const_iterator pos = lower_bound(key);
			return pos == end() || this->comp(key, GetKey(pos.base())) ? end() : pos;
		}

		size_type count(const key_type& key) const {
			pair_cc pair = equal_range(key);
			size_type n = ft::distance(pair.first, pair.second);
			return n;
		}

		iterator lower_bound(const key_type& key) { return iterator(Lbound(key)); }
		const_iterator lower_bound(const key_type& key) const { return const_iterator(Lbound(key)); }
		iterator upper_bound(const key_type& key) { return iterator(Ubound(key)); }
		const_iterator upper_bound(const key_type& key) const { return const_iterator(Ubound(key)); }

		pair_ii equal_range(const key_type& key) { return pair_ii(lower_bound(key), upper_bound(key)); }
		pair_cc equal_range(const key_type& key) const { return pair_cc(lower_bound(key), upper_bound(key)); }

		void swap(Tree& X) {
			if (get_allocator() == X.get_allocator()) {
				ft::swap(_alloc_node, X._alloc_node);
				ft::swap(_alloc_val, X._alloc_val);
				ft::swap(_alloc_ptr, X._alloc_ptr);
			}
			ft::swap(this->comp, X.comp);
			ft::swap(_head, X._head);
			ft::swap(_size, X._size);
		}


	protected:
		Node*								_head;
		size_type							_size;
		allocator_type						_alloc_val;
		allocator_node						_alloc_node;
		allocator_pointer					_alloc_ptr;

		Node* Buynode(Node* x, char color) {
			Node* node = _alloc_node.allocate(1);
			_alloc_ptr.construct(&node->_left, NULL);
			_alloc_ptr.construct(&node->_right, NULL);
			_alloc_ptr.construct(&node->_parent, x);
			node->_color = color;
			node->_isnil = false;
			return node;
		}

		void Construct_value(pointer ptr, const value_type& val) { _alloc_val.construct(ptr, val); }
		void Destroy_value(pointer ptr) { _alloc_val.destroy(ptr); }

		void Copy(const Tree& x) {
			Root() = Copy(x.Root(), _head);
			_size = x.size();
			if (!(Root()->_isnil)) {
				Lmost() = Min(Root());
				Rmost() = Max(Root());
			}
			else
				Lmost() = _head, Rmost() = _head;
		}

		Node* Copy(Node* x, Node* ptr) {
			Node* tmp = _head;
			if (!x->_isnil) {
				Node* y = Buynode(ptr, x->_color);
				try {
					Construct_value(&y->_value, x->_value);
				}
				catch(...) {
					Freenode(y);
					Erase(tmp);
					throw;
				}
				y->_left = _head;
				y->_right = _head;
				if (tmp->_isnil)
					tmp = y;
				try {
					y->_left = Copy(x->_left, y);
					y->_right = Copy(x->_right, y);
				}
				catch(...) {
					Erase(tmp);
					throw;
				}
			}
			return tmp;
		}

		void Erase(Node* ptr) {
			for (Node* tmp = ptr; !(tmp->_isnil); ptr = tmp) {
				Erase(tmp->_right);
				tmp = tmp->_left;
				Destroy_value(&ptr->_value);
				Freenode(ptr);
			}
		}

		void Freenode(Node* ptr) {
			_alloc_ptr.destroy(&ptr->_parent);
			_alloc_ptr.destroy(&ptr->_right);
			_alloc_ptr.destroy(&ptr->_left);
			_alloc_node.deallocate(ptr, 1);
		}

		const key_type& GetKey(Node* ptr) const {
			return this->getKeyByVal(ptr->_value);
		}

		void Init() {
			_head = Buynode(0, BLACK);
			_head->_isnil = true;
			Root() = _head;
			Lmost() = _head;
			Rmost() = _head;
			_size = 0;
		}

		iterator Insert(bool Addleft, Node* Y, const value_type& val) {
			if (max_size() - 1 <= _size)
				throw std::length_error("map/set<T> too long");
			Node* Z = Buynode(Y, RED);
			Z->_left = _head;
			Z->_right = _head;
			try {
				Construct_value(&Z->_value, val);
			}
			catch(...) {
				Freenode(Z);
				throw;
			}
			++_size;
			if (Y == _head) {
				Root() = Z;
				Lmost() = Z;
				Rmost() = Z;
			}
			else if (Addleft) {
				Y->_left = Z;
				if (Y == Lmost())
					Lmost() = Z;
			}
			else {
				Y->_right = Z;
				if (Y == Rmost())
					Rmost() = Z;
			}
			for (Node* X = Z; X->_parent->_color == RED; ) {
				if (X->_parent == X->_parent->_parent->_left) {
					Y = X->_parent->_parent->_right;
					if (Y->_color == RED) {
						X->_parent->_color = BLACK;
						Y->_color = BLACK;
						X->_parent->_parent->_color = RED;
						X = X->_parent->_parent;
					}
					else {
						if (X == X->_parent->_right) {
							X = X->_parent;
							Lrotate(X);
						}
						X->_parent->_color = BLACK;
						X->_parent->_parent->_color = RED;
						Rrotate(X->_parent->_parent);
					}
				}
				else {
					Y = X->_parent->_parent->_left;
					if (Y->_color == RED) {
						X->_parent->_color = BLACK;
						Y->_color = BLACK;
						X->_parent->_parent->_color = RED;
						X = X->_parent->_parent;
					}
					else {
						if (X == X->_parent->_left) {
							X = X->_parent;
							Rrotate(X);
						}
						X->_parent->_color = BLACK;
						X->_parent->_parent->_color = RED;
						Lrotate(X->_parent->_parent);
					}
				}	
			}
			Root()->_color = BLACK;
			return iterator(Z);
		}

		Node* Lbound(const key_type& key) const {
			Node* X = Root();
			Node* Y = _head;
			while (!(X->_isnil)) {
				if (this->comp(GetKey(X), key))
					X = X->_right;
				else
					Y = X, X = X->_left;
			}
			return Y;
		}

		Node*& Lmost() { return _head->_left; }
		Node*& Lmost() const { return _head->_left; }

		void Lrotate(Node* X) {
			Node* Y = X->_right;
			X->_right = Y->_left;
			if (!Y->_left->_isnil)
				Y->_left->_parent = X;
			Y->_parent = X->_parent;
			if (X == Root())
				Root() = Y;
			else if (X == X->_parent->_left)
				X->_parent->_left = Y;
			else
				X->_parent->_right = Y;
			Y->_left = X;
			X->_parent = Y;
		}

		static Node* Max(Node* ptr) {
			while(!ptr->_right->_isnil)
				ptr = ptr->_right;
			return ptr;
		}

		static Node* Min(Node* ptr) {
			while(!ptr->_left->_isnil)
				ptr = ptr->_left;
			return ptr;
		}

		Node*& Rmost() { return _head->_right; }
		Node*& Rmost() const { return _head->_right; }

		Node*& Root() { return _head->_parent; }
		Node*& Root() const { return _head->_parent; }

		void Rrotate(Node* X) {
			Node* Y = X->_left;
			X->_left = Y->_right;
			if (!Y->_right->_isnil)
				Y->_right->_parent = X;
			Y->_parent = X->_parent;
			if (X == Root())
				Root() = Y;
			else if (X == X->_parent->_right)
				X->_parent->_right = Y;
			else
				X->_parent->_left = Y;
			Y->_right = X;
			X->_parent = Y;
		}

		Node* Ubound(const key_type& key) const {
			Node* X = Root();
			Node* Y = _head;
			while (!(X->_isnil)) {
				if (this->comp(key, GetKey(X)))
					Y = X, X = X->_left;
				else
					X = X->_right;
			}
			return Y;
		}
	};

	// * === NON-MEMBER FUNCTIONS === * //

	template <class Tr>
  	bool operator==(const Tree<Tr>& lhs, const Tree<Tr>& rhs) {	return lhs.size() == rhs.size()	&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <class Tr>
  	bool operator!=(const Tree<Tr>& lhs, const Tree<Tr>& rhs) {	return !(lhs == rhs); }

	template <class Tr>
  	bool operator<(const Tree<Tr>& lhs, const Tree<Tr>& rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class Tr>
  	bool operator>(const Tree<Tr>& lhs, const Tree<Tr>& rhs) { return rhs < lhs; }

	template <class Tr>
  	bool operator<=(const Tree<Tr>& lhs, const Tree<Tr>& rhs) {	return !(rhs < lhs); }

	template <class Tr>
  	bool operator>=(const Tree<Tr>& lhs, const Tree<Tr>& rhs) {	return !(lhs < rhs); }

	template<class Tr>
		void swap(Tree<Tr>& x, Tree<Tr>& y) { x.swap(y); }
}      

#endif