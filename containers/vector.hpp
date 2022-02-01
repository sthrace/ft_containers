#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <stdexcept>
# include "../common/iterator.hpp"
# include "../common/algorithm.hpp"

namespace ft {
	template < class T, typename Alloc = std::allocator<T> > class vector {
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*										pointer;
			typedef const T*								const_pointer;
			typedef ft::vector_iterator<value_type>			iterator;
			typedef ft::vector_iterator<value_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef size_t							    	size_type;
			typedef std::ptrdiff_t							difference_type;

			// * === MEMBER FUNCTIONS === * //

			// * == Constructor == * //
			explicit vector() { Buy(0); }
			explicit vector(size_type n, const value_type& val = value_type()) {
				if (Buy(n))
					_last = Ufill(_first, n, val);
			}
			template <class InputIterator>
			vector(InputIterator first, InputIterator last) {
				Construct(first, last, Iter_cat(first));
			}
			vector(const vector& x) {
				if (Buy(x.size()))
					_last = Ucopy(x.begin(), x.end(), _first);
			}
			// * == Destructor == * //
			~vector(void) { Clear(); }
			// * == Operator= == * //
			vector& operator=(const vector& x) {
				if (this == &x) { ; }
				else if (x.size() == 0)
					Clear();
				else if (x.size() < size()) {
					pointer ptr = ft::copy(x.begin(), x.end(), _first);
					Destroy(ptr, _last);
					_last = _first + x.size();
				}
				else if (x.size() <= capacity()) {
					const_iterator iter = x.begin() + size();
					ft::copy(x.begin(), iter, _first);
					_last = Ucopy(iter, x.end(), _last);
				}
				else {
					Destroy(_first, _last);
					_alloc.deallocate(_first, _end - _first);
				}
				if (Buy(x.size()))
					_last = Ucopy(x.begin(), x.end(), _first);
				return *this;
			}
			// * === ITERATORS === * //
			// * == Begin == * //
			iterator begin() { return iterator(_first); }
			const_iterator begin() const { return const_iterator(_first); }
			// * == End == * //
			iterator end() { return iterator(_last); }
			const_iterator end() const { return const_iterator(_last); }
			// * == Rbegin == * //
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			// * == Rend == * //
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

			// * === CAPACITY === * //

			// * == Size == * //
			size_type size() const { return _first == 0 ? 0 : _last - _first; }
			// * == Max_size == * //
			size_type max_size() const { return _alloc.max_size(); }
			// * == Resize == * //
			void resize(size_type n, value_type val = value_type()) {
				if (size() < n)
					insert(end(), n - size(), val);
				else if (n < size())
					erase(begin() + n, end());
			}
			// * == Capacity == * //
			size_type capacity() const { return _first == 0 ? 0 : _end - _first; }
			// * == Empty == * //
			bool empty() const { return size() == 0; }
			// * == Reserve == * //
			void reserve(size_type n) {
				if (max_size() < n)
					Xlen();
				else if (capacity() < n) {
					pointer ptr = _alloc.allocate(n);
					try {
						Ucopy(begin(), end(), ptr);
					}
					catch(...) {
						_alloc.deallocate(ptr, n);
						throw;
					}
					if (_first != 0) {
						Destroy(_first, _last);
						_alloc.deallocate(_first, _end - _first);
					}
					_end = ptr + n;
					_last = ptr + size();
					_first = ptr;
				}
			}

			// * === ELEMENT ACCESS === * //

			// * == Operator[] == * //
			reference operator[](size_type n) { return *(begin() + n); }
			const_reference operator[](size_type n) const { return *(begin() + n); }
			// * == At == * //
			reference at(size_type n) {
				if (size() <= n)
					Xran();
				return *(begin() + n);
			}

			const_reference at(size_type n) const {
				if (size() <= n)
					Xran();
				return *(begin() + n);
			}
			// * == Front == * //
			reference front() { return *begin(); }
			const_reference front() const { return *begin(); }
			// * == Back == * //
			reference back() { return *(end() - 1); }
			const_reference back() const { return *(end() - 1); }
			// * == Data == * //
			value_type* data() { 
				return _first;
			}
			const value_type* data() const {
				return _first;
			}

			// * === MODIFIERS === * //

			// * == Assign == * //
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last) {
				Assign(first, last, Iter_cat(first));
			}
			void assign(size_type n, const value_type& val) {
				value_type tmp = val;
				erase(begin(), end());
				insert(begin(), n, tmp);
			}
			// * == Push_back == * //
			void push_back(const value_type& val) { insert(end(), val); }
			// * == Pop_back == * //
			void pop_back() { erase(end() - 1); }
			// * == Insert == * //
			iterator insert(iterator pos, const value_type& val) {
				size_type offset = size() == 0 ? 0 : pos - begin();
				insert(pos, static_cast<size_type>(1), val);
				return begin() + offset;
			}
			void insert(iterator pos, size_type n, const value_type& val) {
				value_type tmpval = val;
				size_type cap = capacity();
				if (n == 0) { ; }
				else if (max_size() - size() < n)
					Xlen();
				else if (cap < size() + n) {
					cap = max_size() - cap / 2 < cap ? 0 : cap + cap / 2;
					if (cap < size() + n)
						cap = size() + n;
					pointer ptr = _alloc.allocate(cap);
					pointer tmpptr;
					try {
						tmpptr = Ucopy(begin(), pos, ptr);
						tmpptr = Ufill(tmpptr, n, tmpval);
						Ucopy(pos, end(), tmpptr);
					}
					catch(...) {
						Destroy(ptr, tmpptr);
						_alloc.deallocate(ptr, cap);
						throw;
					}
					if (_first != 0) {
						Destroy(_first, _last);
						_alloc.deallocate(_first, _end - _first);
					}
					_end = ptr + cap;
					_last = ptr + size() + n;
					_first = ptr;
				}
				else if (static_cast<size_type>(end() - pos) < n) {
					Ucopy(pos, end(), pos.base() + n);
					try {
						Ufill(_last, n - (end() - pos), tmpval);
					}
					catch(...) {
						Destroy(pos.base() + n, _last + n);
						throw;
					}
					_last += n;
					ft::fill(pos, end() - n, tmpval);
				}
				else {
					iterator tmpend = end();
					_last = Ucopy(tmpend - n, tmpend, _last);
					ft::reverse_copy(pos, tmpend - n, tmpend);
					ft::fill(pos, pos + n, tmpval);
				}
			}
			template <class InputIterator>
			void insert(iterator pos, InputIterator first, InputIterator last) {
				Insert(pos, first, last, Iter_cat(first));
			}
			// * == Erase == * //
			iterator erase(iterator pos) {
				ft::copy(pos + 1, end(), pos);
				Destroy(_last - 1, _last);
				--_last;
				return pos;
			}
			iterator erase(iterator first, iterator last) {
				if (first != last) {
					pointer ptr = ft::copy(last, end(), first.base());
					Destroy(ptr, _last);
					_last = ptr;
				}
				return first;
			}
			// * == Swap == * //
			void swap(vector& x) {
				if (_alloc == x._alloc) {
					ft::swap(_first, x._first);
					ft::swap(_last, x._last);
					ft::swap(_end, x._end);
				}
				else { ft::vector<T> temp = *this; *this = x; x = temp; }
			}
			// * == Clear == * //
			void clear() { erase(begin(), end()); }

			// * === ALLOCATOR === * //

			// * == Get_allocator == * //
			allocator_type get_allocator() const { return _alloc; }

			// * === METHODS USED BY TEMPLATE FUNCTIONS === * //

			bool Eq(const vector &x) const {
				return (size() == x.size() && ft::equal(begin(), end(), x.begin()));
			}

			bool Lt(const vector &x) const {
				return ft::lexicographical_compare(begin(), end(), x.begin(), x.end());
			}

		protected:
			pointer _first, _last, _end;
			allocator_type _alloc;

			bool Buy(size_type n) {
				_first = 0, _last = 0, _end = 0;
				if (n == 0)
					return false;
				else {
					_first = _alloc.allocate(n);
					_last = _first;
					_end = _first + n;
					return true;
				}
			}
			void Clear() {
				if (_first != 0) {
					Destroy(_first, _last);
					_alloc.deallocate(_first, _end - _first);
				}
				_first = 0, _last = 0, _end = 0;
			}
			void Destroy(pointer first, pointer last) {
				for (; first != last; ++first)
					_alloc.destroy(first);
			}
			template <class It>
			pointer Ucopy(It first, It last, pointer ptr) {
				pointer tmp = ptr;
				try {
					for (; first != last; ++ptr, ++first)
						_alloc.construct(ptr, *first);
				}
				catch(...) {
					Destroy(tmp, ptr);
					throw;
				}
				return ptr;
			}
			pointer Ufill(pointer ptr, size_type n, const value_type& val) {
				pointer tmp = ptr;
				try {
					for (; 0 < n; --n, ++ptr)
						_alloc.construct(ptr, val);
				}
				catch(...) {
					Destroy(tmp, ptr);
					throw;
				}
				return ptr;
			}
			template <class It>
			void Construct(It first, It last, ft::Int_iterator_tag) {
				size_type n = static_cast<size_type>(first);
				if (Buy(n))
					_last = Ufill(_first, n, static_cast<value_type>(last));
			}
			template <class It>
			void Construct(It first, It last, ft::input_iterator_tag) {
				Buy(0);
				insert(begin(), first, last);
			}
			template <class It>
			void Insert(iterator pos, It first, It last, ft::Int_iterator_tag) {
				insert(pos, static_cast<size_type>(first), static_cast<value_type>(last));
			}
			template <class It>
			void Insert(iterator pos, It first, It last, ft::input_iterator_tag) {
				for (; first != last; ++first, ++pos)
					pos = insert(pos, *first);
			}
			template <class It>
			void Insert(iterator pos, It first, It last, ft::forward_iterator_tag) {
				size_type dist = ft::distance(first, last);
				size_type cap = capacity();
				if (dist == 0) { ; }
				else if (max_size() - size() < dist)
					Xlen();
				else if (cap < size() + dist) {
					cap = max_size() - cap / 2 < cap ? 0 : cap + cap / 2;
					if (cap < size() + dist)
						cap = size()+ dist;
					pointer ptr = _alloc.allocate(cap);
					pointer tmpptr;
					try {
						tmpptr = Ucopy(begin(), pos, ptr);
						tmpptr = Ucopy(first, last, tmpptr);
						Ucopy(pos, end(), tmpptr);
					}
					catch(...) {
						Destroy(ptr, tmpptr);
						_alloc.deallocate(ptr, cap);
						throw;
					}
					if (_first != 0) {
						Destroy(_first, _last);
						_alloc.deallocate(_first, _end - _first);
					}
					_end = ptr + cap;
					_last = ptr + size() + dist;
					_first = ptr;
				}
				else if (static_cast<size_type>(end() - pos) < dist) {
					Ucopy(pos, end(), pos.base() + dist);
					It mid = first;
					ft::advance(mid, end() - pos);
					try {
						Ucopy(mid, last, _last);
					}
					catch(...) {
						Destroy(pos.base() + dist, _last + dist);
						throw;
					}
					_last += dist;
					ft::copy(first, mid, pos);
				}
				else if (0 < dist) {
					iterator tmpend = end();
					_last = Ucopy(tmpend - dist, tmpend, _last);
					ft::reverse_copy(pos, tmpend - dist, tmpend);
					ft::copy(first, last, pos);
				}
			}
			template <class It>
			void Assign(It first, It last, ft::Int_iterator_tag) {
				assign(static_cast<size_type>(first), static_cast<value_type>(last));
			}
			template <class It>
			void Assign(It first, It last, ft::input_iterator_tag) {
				erase(begin(), end());
				insert(begin(), first, last);
			}
			void Xlen() const { throw std::length_error("vector<T> too long"); }
			void Xran() const { throw std::out_of_range("vector<T> subscript"); }
	}; // class vector

	// * === NON-MEMBER FUNCTION OVERLOADS === * //

	// * == Relational operators == * //

	template<class T, class A>
	bool operator==(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return lhs.Eq(rhs); }

	template<class T, class A>
	bool operator!=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return !(lhs == rhs); }

	template<class T, class A>
	bool operator<(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return lhs.Lt(rhs); }

	template<class T, class A>
	bool operator<=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return !(rhs < lhs); }

	template<class T, class A>
	bool operator>(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return rhs < lhs; }

	template<class T, class A>
	bool operator>=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return !(rhs > lhs); }

	// * == Swap == * //

	template <class T, class A>
	void swap (ft::vector<T, A>& lhs, ft::vector<T, A>&rhs) { lhs.swap(rhs); }

} // namespace ft

#endif