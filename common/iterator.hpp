#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstdlib>
# include "tree.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct Int_iterator_tag {};

	template <typename C, typename T, typename Dist = std::ptrdiff_t, typename Pt = T*, typename Rt = T&>
	struct iterator {
		typedef C		iterator_category;
		typedef T		value_type;
		typedef Dist	difference_type;
		typedef Pt		pointer;
		typedef Rt		reference;
	};

	template<typename T, typename D, typename Pt, typename Rt>
	struct BidIt : public iterator<ft::bidirectional_iterator_tag, T, D, Pt, Rt> {};

	template<typename T, typename D, typename Pt, typename Rt>
	struct RanIt : public iterator<ft::random_access_iterator_tag, T, D, Pt, Rt> {};

	struct OutIt : public iterator<ft::output_iterator_tag, void, void, void, void> {};

	template <typename Iter>
	struct iterator_traits {
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag			iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag			iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
	};

	template <class C, class T, class D, class Pt, class Rt> inline
	C Iter_cat(const iterator<C, T, D, Pt, Rt>&) {
		C X;
		return X;
	}

	template<typename T>
	ft::random_access_iterator_tag Iter_cat(const T*) {
		ft::random_access_iterator_tag X;
		return X;
	}

	inline ft::Int_iterator_tag Iter_cat(bool) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(char) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(signed char) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(unsigned char) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(wchar_t) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(short) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(unsigned short) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(int) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(unsigned int) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(long) {
		ft::Int_iterator_tag X;
		return X;
	}
	inline ft::Int_iterator_tag Iter_cat(unsigned long) {
		ft::Int_iterator_tag X;
		return X;
	}

	template <typename Iter, typename D>
	void	my_distance_helper(Iter first, Iter last, D& dist, ft::input_iterator_tag) {
		for(; first != last; ++first)
			++dist;
	}

	template <typename Iter, typename D>
	void	my_distance_helper(Iter first, Iter last, D& dist, ft::random_access_iterator_tag) {
		dist += last - first;
	}

	template <typename Iter>
	typename ft::iterator_traits<Iter>::difference_type distance (Iter first, Iter last) {
		typename ft::iterator_traits<Iter>::difference_type dist = 0;
		my_distance_helper(first, last, dist, ft::Iter_cat(first));
		return dist;
	}

	template<typename Iter>
	void my_advance_helper(Iter& iter, ft::input_iterator_tag, int n) {
		for (int i = 0; i < n; ++i) {
			++iter;
		}
	}

	template<typename Iter>
	void my_advance_helper(Iter& iter, ft::bidirectional_iterator_tag, int n) {
		if (n > 0) {
			while (n--) {
				++iter;
			}
		}
		else {
			while (n++) {
				--iter;
			}
		}
	}

	template<typename Iter>
	void my_advance_helper(Iter& iter, ft::random_access_iterator_tag, int n) {
		iter += n;
	}

	template<typename Iter>
	void advance(Iter& iter, int n) {
		my_advance_helper(iter, typename ft::iterator_traits<Iter>::iterator_category(), n);
	}

	template<typename T>
	class vector_iterator : public ft::iterator<random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

	protected:
		pointer _ptr;

	public:
		vector_iterator(void) { _ptr = NULL; }
		vector_iterator(pointer ptr) : _ptr(ptr) {}
		vector_iterator(const vector_iterator& x) { _ptr = x._ptr; }
		~vector_iterator() {}

		vector_iterator &operator=(const vector_iterator& x) {
			if (this != &x) {
				_ptr = x._ptr;
			}
			return *this;
		}

		vector_iterator& operator++() {
			_ptr++;
			return *this;
		}

		vector_iterator operator++(int) { 
			vector_iterator temp = *this;
			_ptr++;
			return temp;
		}

		vector_iterator& operator--() {
			_ptr--;
			return *this;
		}

		vector_iterator operator--(int) { 
			vector_iterator temp = *this;
			_ptr--;
			return temp;
		}

		vector_iterator operator+(difference_type n) { 
			return vector_iterator(_ptr + n); 
		}

		vector_iterator operator-(difference_type n) { 
			return vector_iterator(_ptr - n);  
		}

		vector_iterator& operator+=(difference_type n) {
			_ptr += n;
			return *this; 
		}

		vector_iterator& operator-=(difference_type n) {
			_ptr -= n;
			return *this; 
		}
			
		reference& operator*() { return *_ptr; }
		const reference& operator*() const { return *_ptr; }
		pointer operator->() { return &**_ptr; }
		const pointer operator->() const { return &**_ptr; }
		reference operator[](difference_type idx) { return *(*this + idx); }
		const reference operator[](difference_type idx) const { return *(*this + idx); }

		difference_type operator-(vector_iterator const &x) const {
			return (this->_ptr - x._ptr);
		}

		pointer	base() const {
			return _ptr;
		}
	};

	template <typename T>
	ft::vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type n, const ft::vector_iterator<T> &iter) {
		return iter + n;
	}

	template <typename T, typename U>
	bool operator==(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<U> &rhs) { 
		return lhs.base() == rhs.base(); 
	}
	template <typename T, typename U>
	bool operator!=(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<U> &rhs) { 
		return !(lhs == rhs); 
	}
	template <typename T, typename U>
	bool operator<(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<U> &rhs) { 
		return lhs.base() < rhs.base(); 
	}
	template <typename T, typename U>
	bool operator>(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<U> &rhs) { 
		return rhs < lhs; 
	}
	template <typename T, typename U>
	bool operator>=(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<U> &rhs) { 
		return !(lhs < rhs); 
	}
	template <typename T, typename U>
	bool operator<=(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<U> &rhs) { 
		return !(rhs < lhs); 
	}

	template <typename Iter>
	class reverse_iterator {
	public:
	typedef Iter													iterator_type;
	typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iter>::value_type			value_type;
	typedef	typename ft::iterator_traits<Iter>::difference_type		difference_type;
	typedef	typename ft::iterator_traits<Iter>::pointer				pointer;
	typedef	typename ft::iterator_traits<Iter>::reference			reference;

	protected:
		iterator_type		current;

	public:
		reverse_iterator(void) {}
		explicit reverse_iterator(Iter base) : current(base) {}
		template<typename U>
		reverse_iterator(const U& X) : current(X.base()) {}
		~reverse_iterator() {}

		iterator_type base() const { return current; }

		reference operator*() { 
			iterator_type Temp = current;
			return (*--Temp);
		}

		const reference operator*() const { 
			iterator_type Temp = current;
			return (*--Temp);
		}

		pointer operator->() {
			return (&**this);
		}

		const pointer operator->() const {
			return (&**this);
		}

		reverse_iterator operator++() { 
			--current;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator Temp = *this;
			--current;
			return Temp;
		}

		reverse_iterator operator--() { 
			++current;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator Temp = *this;
			++current;
			return Temp;
		}

		reverse_iterator operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		reverse_iterator operator-=(difference_type n) {
			current += n;
			return *this;
		}

		reverse_iterator operator+(difference_type n) {
			return reverse_iterator<Iter>(current - n);
		}

		const reverse_iterator operator+(difference_type n) const {
			return reverse_iterator<Iter>(current - n);
		}

		reverse_iterator operator-(difference_type n) {
			return reverse_iterator<Iter>(current + n);
		}

		const reverse_iterator operator-(difference_type n) const {
			return reverse_iterator<Iter>(current + n);
		}

		reverse_iterator operator[](difference_type n) {
			return *(this + n);
		}

		const reverse_iterator operator[](difference_type n) const {
			return *(this + n);
		}
	};

	template <typename T>
	ft::reverse_iterator<T> operator+(typename ft::reverse_iterator<T>::difference_type n, const ft::reverse_iterator<T> &iter) {
		return iter + n;
	}

	template <typename T, typename U>
	bool operator==(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<U> &rhs) { 
		return lhs.base() == rhs.base(); 
	}
	template <typename T, typename U>
	bool operator!=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<U> &rhs) { 
		return !(lhs == rhs); 
	}
	template <typename T, typename U>
	bool operator<(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<U> &rhs) { 
		return lhs.base() < rhs.base(); 
	}
	template <typename T, typename U>
	bool operator>(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<U> &rhs) { 
		return rhs < lhs; 
	}
	template <typename T, typename U>
	bool operator>=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<U> &rhs) { 
		return !(lhs < rhs); 
	}
	template <typename T, typename U>
	bool operator<=(const ft::reverse_iterator<T> &lhs, const ft::reverse_iterator<U> &rhs) { 
		return !(rhs < lhs); 
	}

	template<class Node, class T, class P, class R>
	class tree_iterator : public ft::iterator<bidirectional_iterator_tag, Node>
	{
		public:
		typedef T																			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;

		tree_iterator(void) { _ptr = NULL; }
		tree_iterator(Node* ptr) : _ptr(ptr) {}
		tree_iterator(const tree_iterator& x) { _ptr = x._ptr; }
		~tree_iterator() {}

		tree_iterator &operator=(const tree_iterator& x) {
			if (this != &x) {
				_ptr = x._ptr;
			}
			return *this;
		}

		tree_iterator& operator++() {
			Inc();
			return *this;
		}

		tree_iterator operator++(int) { 
			tree_iterator temp = *this;
			++*this;
			return temp;
		}

		tree_iterator& operator--() {
			Dec();
			return *this;
		}

		tree_iterator operator--(int) { 
			tree_iterator temp = *this;
			--*this;
			return temp;
		}

		tree_iterator& operator+=(difference_type n) {
			_ptr += n;
			return *this; 
		}

		tree_iterator& operator-=(difference_type n) {
			_ptr -= n;
			return *this; 
		}
			
		reference& operator*() { return _ptr->value; }
		const reference& operator*() const { return _ptr->value; }
		pointer operator->() { return &**_ptr; }
		const pointer operator->() const { return &**_ptr; }

		bool operator==(const tree_iterator& x) { return _ptr == x._ptr; }
		bool operator!=(const tree_iterator& x) { return !(_ptr == x._ptr); }

		Node*	base() const {
			return _ptr;
		}
		protected:
			Node*	_ptr;

			void Dec() {
				if (_ptr->isnil)
					_ptr = _ptr->right;
				else if (!_ptr->left->isnil)
					_ptr = Max(_ptr->right);
				else {
					Node* tmp;
					while(!((tmp = _ptr->parent->isnil)) && _ptr == _ptr->left)
						_ptr = tmp;
					if (!tmp->isnil)
						_ptr = tmp;
				}
			}
			void Inc() {
				if (_ptr->isnil)
					;
				else if (!_ptr->right->isnil)
					_ptr = Min(_ptr->right);
				else {
					Node tmp;
					while((!(tmp = _ptr->parent->isnil)) && _ptr == _ptr->right)
						_ptr = tmp;
					_ptr = tmp;
				}
			}
			Node*	Max(Node* ptr) {
				while (!ptr->right->_isNil)
					ptr = ptr->_right;
				return ptr;
			}

			Node*	Min(Node* ptr) {
				while (!ptr->left->_isNil)
					ptr = ptr->left;
				return ptr;
			}
	};

	template<class Node, class T, class P, class R>
	class const_tree_iterator : public ft::iterator<bidirectional_iterator_tag, Node>
	{
		public:
		typedef T																			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;

		const_tree_iterator(void) { _ptr = NULL; }
		const_tree_iterator(Node* ptr) : _ptr(ptr) {}
		const_tree_iterator(const const_tree_iterator& x) { _ptr = x._ptr; }
		~const_tree_iterator() {}

		const_tree_iterator &operator=(const const_tree_iterator& x) {
			if (this != &x) {
				_ptr = x._ptr;
			}
			return *this;
		}

		const_tree_iterator& operator++() {
			Inc();
			return *this;
		}

		const_tree_iterator operator++(int) { 
			const_tree_iterator temp = *this;
			++*this;
			return temp;
		}

		const_tree_iterator& operator--() {
			Dec();
			return *this;
		}

		const_tree_iterator operator--(int) { 
			const_tree_iterator temp = *this;
			--*this;
			return temp;
		}

		const_tree_iterator& operator+=(difference_type n) {
			_ptr += n;
			return *this; 
		}

		const_tree_iterator& operator-=(difference_type n) {
			_ptr -= n;
			return *this; 
		}
			
		reference& operator*() { return _ptr->value; }
		const reference& operator*() const { return _ptr->value; }
		pointer operator->() { return &**_ptr; }
		const pointer operator->() const { return &**_ptr; }

		bool operator==(const const_tree_iterator& x) { return _ptr == x._ptr; }
		bool operator!=(const const_tree_iterator& x) { return !(_ptr == x._ptr); }

		Node*	base() const {
			return _ptr;
		}
		protected:
			Node*	_ptr;

			void Dec() {
				if (_ptr->isnil)
					_ptr = _ptr->right;
				else if (!_ptr->left->isnil)
					_ptr = Max(_ptr->right);
				else {
					Node* tmp;
					while(!((tmp = _ptr->parent->isnil)) && _ptr == _ptr->left)
						_ptr = tmp;
					if (!tmp->isnil)
						_ptr = tmp;
				}
			}
			void Inc() {
				if (_ptr->isnil)
					;
				else if (!_ptr->right->isnil)
					_ptr = Min(_ptr->right);
				else {
					Node tmp;
					while((!(tmp = _ptr->parent->isnil)) && _ptr == _ptr->right)
						_ptr = tmp;
					_ptr = tmp;
				}
			}
			Node*	Max(Node* ptr) {
				while (!ptr->right->_isNil)
					ptr = ptr->_right;
				return ptr;
			}

			Node*	Min(Node* ptr) {
				while (!ptr->left->_isNil)
					ptr = ptr->left;
				return ptr;
			}
	};
}

#endif