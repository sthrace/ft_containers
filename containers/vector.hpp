#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <stdexcept>
# include "../iterators/reverse_iterator.hpp"
# include "../common/algorithm.hpp"
# include "../common/type_traits.hpp"
# include "../common/utility.hpp"

namespace ft
{
	template <typename T, typename A = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef A										allocator_type;
			typedef size_t							    	size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*										pointer;
			typedef const T*								const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<value_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			// * ============ MEMBER FUNCTIONS ============ * //

			explicit vector(const allocator_type& alloc = allocator_type()) {
				Buy(0);
			}

			explicit vector(size_type n, const value_type& val = value_type(),	const allocator_type& alloc = allocator_type()) {
				if (Buy(n))
					_last = Ufill(_first, n, val);
			}

			template <typename Iter>
			vector(Iter first, Iter last, const allocator_type& alloc = allocator_type()) {
				Construct(first, last); 				
			}

			vector(const vector& X) {
				if (Buy(X.size()))
					_last = Ucopy(X.begin(), X.end(), _first);
			 }

			virtual ~vector() {
				Clear();
			}

			vector &operator=(const vector& X) {
				if (this == &X) { return *this; }
				else if (X.size() == 0) { Clear(); }
				else if (X.size() <= size()) {
					pointer tmp = ft::copy(X.begin(), X.end(), _first);
					Destroy(tmp, _last);
					_last = _first + X.size();
				}
				else if (X.size() <= capacity()) {
					const_iterator tmp = X.begin() + size();
					ft::copy(X.begin(), tmp, _first);
					_last = Ucopy(tmp, X.end(), _last);
				}
				else {
					Destroy(_first, _last);
					_alloc.deallocate(_first, _end - _first);
					if (Buy(X.size()))
						_last = Ucopy(X.begin(), X.end(), _first);
				}
				return *this;
			}

			void assign(size_type cnt, const T& val) {
				T tmp = val;
				erase(begin(), end());
				insert(begin(), cnt, tmp);
			}

			template <typename Iter>
			void assign(Iter first, Iter last, typename ft::enable_if<!ft::is_integral<Iter>::value >::type* = 0) {
				erase(begin(), end());
				insert(begin(), first, last);
			}

			template <typename Iter>
			void assign(Iter first, Iter last, typename ft::enable_if<ft::is_integral<Iter>::value >::type* = 0) {
				assign(static_cast<size_type>(first), static_cast<size_type>(last));
			}

			allocator_type get_allocator() const { return _alloc; }

			// * ============ ELEMENT ACCESS ============ * //

			reference at(size_type idx) {
				if (size() <= idx) {
					Xran();
				}
				return *(begin() + idx);
			}

			const_reference at(size_type idx) const {
				if (size() <= idx) {
					Xran();
				}
				return *(begin() + idx);
			}

			reference operator[](size_type idx) { return *(begin() + idx); }

			const_reference operator[](size_type idx) const { return *(begin() + idx); }

			reference front() { return *begin(); }

			const_reference front() const { return *begin(); }

			reference back() { return *(end() - 1); }

			const_reference back() const { return *(end() - 1); }

			int* data() { 
				if (size()) {
					return (int *)reinterpret_cast<std::ptrdiff_t>(&_first); 
				}
				return NULL;
			}		

			// * ============ ITERATORS ============ * //

			iterator begin(void) { return iterator(_first); }

			const_iterator begin(void) const { return const_iterator(_first); }

			iterator end(void) { return iterator(_last); }

			const_iterator end(void) const { return const_iterator(_last); }

			reverse_iterator rbegin(void) { return reverse_iterator(end()); }

			const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

			reverse_iterator rend(void) { return reverse_iterator(begin()); }

			const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

			// * ============ CAPACITY ============ * //

			bool empty() const { return size() == 0; }

			size_type size() const { return _first == 0 ? 0 : _last - _first; }

			size_type max_size() const { return _alloc.max_size(); }

			void reserve(size_type n) {
				if (max_size() < n) { Xlen(); }
				else if (capacity() < n) {
					pointer tmp = _alloc.allocate(n);
					try {
						Ucopy(begin(), end(), tmp);
					}
					catch(...) {
						_alloc.deallocate(tmp, n);
						throw;
					}
					if (_first != 0) {
						Destroy(_first,_last);
						_alloc.deallocate(_first, _end - _first);
					}
					_end = tmp + n;
					_last = tmp + size();
					_first = tmp;
				}
			}

			size_type capacity() const { return _first == 0 ? 0 : _end - _first; }

			// * ============ MODIFIERS ============ * //

			void clear() { erase(begin(), end()); }

			iterator insert(iterator pos, const T &val) {
				size_type offset = size() == 0 ? 0 : pos - begin();
				insert(pos, static_cast<size_type>(1), val);
				return begin() + offset;
			}

			void insert(iterator pos, size_type cnt, const T &val) {
				T tmp = val;
				size_type cap = capacity();
				if (cnt == 0) { ; }
				else if (max_size() - size() < cnt) { Xlen(); }
				else if (cap < size() + cnt) {
					cap = max_size() - cap / 2 < cap ? 0 : cap + cap / 2;
					if (cap < size() + cnt) {
						cap = size() + cnt;
					}
					pointer ptr = _alloc.allocate(cap);
					pointer tmpptr;
					try {
						tmpptr = Ucopy(begin(), pos, ptr);
						tmpptr = Ufill(tmpptr, cnt, tmp);
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
					_last = ptr + size() + cnt;
					_first = ptr;
				}
				else if ((size_type)(end() - pos) < cnt) {
					Ucopy(pos, end(), pos.base() + cnt);
					try {
						Ufill(_last, cnt - (end() - pos), tmp);
					}
					catch(...) {
						Destroy(pos.base() + cnt, _last + cnt);
						throw;
					}
					_last += cnt;
					ft::fill(pos, end() - cnt, tmp);
				}
				else {
					iterator tmpend = end();
					_last = Ucopy(tmpend - cnt, tmpend, _last);
					ft::reverse_copy(pos, tmpend - cnt, tmpend);
					ft::fill(pos, pos + cnt, tmp);
				}
			}

			template <typename Iter>
			void insert(iterator pos, Iter first, Iter last, typename ft::enable_if<!ft::is_integral<Iter>::value >::type* = 0) {
					size_type cnt = ft::distance(first, last);
					size_type cap = capacity();
					if (cnt == 0) { ; }
					else if (max_size() - size() < cnt) {
						Xlen();
					}
					else if (cap < size() + cnt) {
						cap = max_size() - cap / 2 < cap ? 0 : cap + cap / 2;
						if (cap < size() + cnt)
							cap = size() + cnt;
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
						_last = ptr + size() + cnt;
						_first = ptr;
					}
					else if ((size_type)(end() - pos) < cnt) {
						Ucopy(pos, end(), pos.base() + cnt);
						Iter mid = first;
						ft::advance(mid, end() - pos);
						try {
							Ucopy(mid, last, _last);
						}
						catch(...) {
							Destroy(pos.base() + cnt, _last + cnt);
							throw;
						}
						_last += cnt;
						ft::copy(first, mid, pos);
					}
					else if (0 < cnt) {
						iterator tmpend = end();
						_last = Ucopy(tmpend - cnt, tmpend, _last);
						ft::reverse_copy(pos, tmpend - cnt, tmpend);
						ft::copy(first, last, pos);
					}
			}

			template <typename Iter>
			void insert(iterator pos, Iter first, Iter last, typename ft::enable_if<ft::is_integral<Iter>::value >::type* = 0) {
				insert(pos, static_cast<size_type>(first), static_cast<value_type>(last));
			}

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

			void push_back(const T& X) {
				insert(end(), X);
			}

			void pop_back() {
				erase(end() - 1);
			}

			void resize(size_type N) {
				resize(N, T());
			}

			void resize(size_type N, T X) {
				if (size() < N)
					insert(end(), N - size(), X);
				else if (N < size())
					erase(begin() + N, end());
			}

			void swap(vector &X) {
				if (_alloc == X._alloc) {
					ft::swap(_first, X._first);
					ft::swap(_last, X._last);
					ft::swap(_end, X._end);
				}
				else {
					vector tmp = *this; 
					*this = X;
					X = tmp;
				}
			}

			// * ============ METHODS USED BY TEMPLATE FUNCTIONS ============ * //

			bool Eq(const vector &X) const {
				return (size() == X.size() && ft::equal(begin(), end(), X.begin()));
			}

			bool Lt(const vector &X) const {
				return ft::lexicographical_compare(begin(), end(), X.begin(), X.end());
			}	

			protected:
				pointer _first, _last, _end;
				allocator_type _alloc;

				template<typename Iter>
				void Construct(Iter first, Iter last, typename ft::enable_if<!std::is_integral<Iter>::value>::type* = 0) {
					Buy(0);
					insert(begin(), first, last);
				}

				template<typename Iter>
				void Construct(Iter first, Iter last, typename ft::enable_if<std::is_integral<Iter>::value>::type* = 0) {
					size_type N = (size_type)first;
					if (Buy(N)) {
						_last = Ufill(_first, N, static_cast<value_type>(last));
					}
				}

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
					for (; first != last; ++first) {
						_alloc.destroy(first);
					}
				}

				template<class Iter>
					pointer Ucopy(Iter first, Iter last, pointer Q) {
						pointer Qs = Q;
						try {
							for (; first != last; ++Q, ++first)
								_alloc.construct(Q, *first);
						}
						catch(...) {
							Destroy(Qs, Q);
							throw;
						}
						return Q;
					}
				
				pointer Ufill(pointer Q, size_type N, const T& X) {
					pointer Qs = Q;
					try {
						for(; 0 < N; --N, ++Q)
							_alloc.construct(Q, X);
					}
					catch(...) {
						Destroy(Qs, Q);
						throw;
					}
					return Q;
				}

				void Xlen() const { throw std::length_error("vector<T> too long"); }

				void Xran() const { throw std::out_of_range("vector<T> subscript"); }

				// template <typename Iter>
				// void InsertIt(iterator pos, Iter first, Iter last, ft::input_iterator_tag) {
				// 	for(; first != last; ++first, ++pos)
				// 		pos = insert(pos, *first);
				// }

				// template<typename Iter>
				// void InsertIt(iterator pos, Iter first, Iter last, ft::forward_iterator_tag) {
				// 	size_type cnt = ft::distance(first, last);
				// 	size_type cap = capacity();
				// 	if (cnt == 0) { ; }
				// 	else if (max_size() - size() < cnt) {
				// 		Xlen();
				// 	}
				// 	else if (cap < size() + cnt) {
				// 		cap = max_size() - cap / 2 < cap ? 0 : cap + cap / 2;
				// 		if (cap < size() + cnt)
				// 			cap = size() + cnt;
				// 		pointer ptr = _alloc.allocate(cap);
				// 		pointer tmpptr;
				// 		try {
				// 			tmpptr = Ucopy(begin(), pos, ptr);
				// 			tmpptr = Ucopy(first, last, tmpptr);
				// 			Ucopy(pos, end(), tmpptr);
				// 		} 
				// 		catch(...) {
				// 			Destroy(ptr, tmpptr);
				// 			_alloc.deallocate(ptr, cap);
				// 			throw;
				// 		}
				// 		if (_first != 0) {
				// 			Destroy(_first, _last);
				// 			_alloc.deallocate(_first, _end - _first);
				// 		}
				// 		_end = ptr + cap;
				// 		_last = ptr + size() + cnt;
				// 		_first = ptr;
				// 	}
				// 	else if ((size_type)(end() - pos) < cnt) {
				// 		Ucopy(pos, end(), pos.base() + cnt);
				// 		Iter mid = first;
				// 		ft::advance(mid, end() - pos);
				// 		try {
				// 			Ucopy(mid, last, _last);
				// 		}
				// 		catch(...) {
				// 			Destroy(pos.base() + cnt, _last + cnt);
				// 			throw;
				// 		}
				// 		_last += cnt;
				// 		ft::copy(first, mid, pos);
				// 	}
				// 	else if (0 < cnt) {
				// 		iterator tmpend = end();
				// 		_last = Ucopy(tmpend - cnt, tmpend, _last);
				// 		ft::reverse_copy(pos, tmpend - cnt, tmpend);
				// 		ft::copy(first, last, pos);
				// 	}
				// }

	}; // class vector

	// * ============ NON MEMBER FUNATIONS ============ * //

template<class T, class A>
	bool operator==(const vector<T, A>& lhs, const vector<T, A>& rhs) { return lhs.Eq(rhs); }

template<class T, class A>
	bool operator!=(const vector<T, A>& lhs, const vector<T, A>& rhs) { return !(lhs == rhs); }

template<class T, class A>
	bool operator<(const vector<T, A>& lhs, const vector<T, A>& rhs) { return lhs.Lt(rhs); }

template<class T, class A>
	bool operator<=(const vector<T, A>& lhs, const vector<T, A>& rhs) { return !(rhs < lhs); }

template<class T, class A>
	bool operator>(const vector<T, A>& lhs, const vector<T, A>& rhs) { return rhs < lhs; }

template<class T, class A>
	bool operator>=(const vector<T, A>& lhs, const vector<T, A>& rhs) { return !(rhs > lhs); }

template <class T, class Alloc>
	void swap (vector<T,Alloc>& lhs, vector<T,Alloc>&rhs) {	lhs.swap(rhs); }
} // namespace

#endif