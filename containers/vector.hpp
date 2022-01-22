// #ifndef VECTOR_HPP
// # define VECTOR_HPP

// # include <memory>
// # include <limits>
// // # include <iterator>
// // # include <cstring>
// // # include <math.h>
// # include "iterator.hpp"
// # include "algorithm.hpp"
// # include "type_traits.hpp"
// # include "utility.hpp"

// namespace ft
// {
// 	template <class T, class A = std::allocator<T> >
// 	class vector {
// 		public:
// 			typedef T										value_type;
// 			typedef A										allocator_type;
// 			typedef size_t							    	size_type;
// 			typedef std::ptrdiff_t							difference_type;
// 			typedef T&										reference;
// 			typedef const T&								const_reference;
// 			typedef T*										pointer;
// 			typedef const T*								const_pointer;
// 			typedef ft::vector_iterator<value_type>			iterator;
// 			typedef ft::vector_iterator<value_type const>	const_iterator;
// 			typedef ft::reverse_iterator<iterator>			reverse_iterator;
// 			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			

// 		protected:
// 			// pointer 		m_vector;
// 			// size_type		m_size;
// 			// size_type		m_capacity;
// 			// allocator_type	m_allocator;
			

// 		public:

// 			// * ============ MEMBER FUNCTIONS ============ * //

// 			explicit vector(const A& alloc = allocator_type()) : m_vector(NULL), m_size(0), m_capacity(0), m_allocator(alloc) {}

// 			explicit vector(size_type n, const value_type& val = value_type(),	const allocator_type& alloc = allocator_type()) : m_size(n), m_capacity(n), m_allocator(alloc) {
// 				m_vector = m_allocator.allocate(n);
// 				for (size_type i = 0; i < n; i++) {
// 					m_allocator.construct(m_vector + i, val);
// 				}
// 			}

// 			template <class InIter>
// 			vector(InIter first, typename std::enable_if<!std::numeric_limits<InIter>::is_integral, InIter>::type last, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
// 				m_size = static_cast<size_type>(last - first);
// 				m_capacity = m_size;
// 				m_vector = m_allocator.allocate(m_capacity);
// 				for (size_type i = 0; i < m_size; i++)	{
// 					m_allocator.construct(m_vector + i, *(first + i));
// 				}
// 			}

// 			vector(const vector& X) {
// 				m_vector = m_allocator.allocate(0);
//         		reserve(X.capacity());
// 				try	{
// 					for (size_type i = 0; i < X.size(); i++)
// 						m_allocator.construct(m_vector + i, *(X.m_vector + i));
// 				}
// 				catch(...)	{
// 					clear();
// 					m_allocator.deallocate(m_vector, m_capacity);
// 				}
// 			 }

// 			virtual ~vector() {
// 				m_allocator.destroy(m_vector);
// 				m_allocator.deallocate(m_vector, m_capacity);
// 			}

// 			vector& operator=(const vector &X) {
// 				if (this == &X)
// 					return *this;
// 				else if (X.size() == 0) { clear(); }
// 				else if (X.size() <= size()) {
// 					for (size_type i = 0; i < X.size(); i++)
// 						m_vector[i] = X.m_vector[i];
// 				}
// 				else if (X.size() <= capacity()) {
// 					for (size_type i = 0; i < X.size(); i++)
// 						m_vector[i] = X.m_vector[i];
// 				}
// 				else {
// 					m_allocator.deallocate(m_vector, m_capacity);
// 					m_vector = m_allocator.allocate(X.capacity());
// 					for (size_type i = 0; i < X.size(); i++)
// 						m_allocator.construct(m_vector + i, *(X.m_vector + i));
// 				}
// 				return *this;
// 			}

// 			void assign(size_type n, const T& val) {
// 				clear();
// 				m_allocator.deallocate(m_vector, m_capacity);
// 				m_vector = m_allocator.allocate(n);
// 				m_capacity = n;
// 				m_size = n;
// 				for (size_type dist = 0; dist < n; dist++)	{
// 					m_allocator.construct(m_vector + dist, val);
// 				}
// 			}

// 			template<class Iter>
// 			void assign(Iter first, typename std::enable_if<!std::numeric_limits<Iter>::is_integer,Iter>::type last)	{
// 				clear();
// 				m_allocator.deallocate(m_vector, m_capacity);
// 				size_type count = static_cast<size_type>(last - first);
// 				m_vector = m_allocator.allocate(count);
// 				m_capacity = count;
// 				m_size = count;
// 				size_type dist = 0;
// 				for (; first != last; first++)
// 				{
// 					m_allocator.construct(m_vector + dist, *first);
// 					dist++;
// 				}
// 			}

// 			allocator_type get_allocator(void) { return m_allocator; }
			
// 			// * ============ ELEMENT ACCESS ============ * //

// 			reference at(size_type idx) { 
// 				if (idx >= m_size)
// 					throw OutOfRange();
// 				return (*(begin() + idx)); 
// 			}
// 			const_reference at(size_type idx) const { 
// 				if (idx >= m_size)
// 					throw OutOfRange();
// 				return (*(begin() + idx)); 
// 			}
// 			reference operator[](size_type idx) { return (*(begin() + idx)); }

// 			const_reference operator[](size_type idx) const { return (*(begin() + idx)); }

// 			reference front() { return (*(begin())); }

// 			const_reference front() const { return (*(begin())); }

// 			reference back() { return (*(end() - 1)); }

// 			const_reference back() const { return (*(end() - 1)); }

// 			int* data() { 
// 				if (m_size) {
// 					return (int *)reinterpret_cast<std::ptrdiff_t>(&m_vector); 
// 				}
// 				return NULL;
// 			}
			
// 			// * ============ ITERATORS ============ * //

// 			iterator begin(void) { return iterator(m_vector); }

// 			const_iterator begin(void) const { return const_iterator(m_vector); }

// 			iterator end(void) { return iterator(m_vector + m_size); }

// 			const_iterator end(void) const { return const_iterator(m_vector + m_size); }

// 			reverse_iterator rbegin(void) { return reverse_iterator(end()); }

// 			const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

// 			reverse_iterator rend(void) { return reverse_iterator(begin()); }

// 			const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }
			
// 			// * ============ CAPACITY ============ * //

// 			bool empty(void) const { return m_size == 0; }

// 			size_type size(void) const { return m_size; }

// 			size_type max_size(void) const { return m_allocator.max_size(); }

// 			void reserve(size_type n) {
// 				if (n > max_size())
// 					throw AllocationFailed();
// 				if (n > m_capacity) {
// 					pointer temp = m_allocator.allocate(n);
// 					for (size_type i = 0; i < m_size; ++i) {
// 						temp[i] = m_vector[i];
// 					}
// 					m_allocator.deallocate(m_vector, m_capacity);
// 					m_capacity = n;
// 					m_vector = temp;
// 				}
// 			}

// 			size_type capacity(void) const { return m_capacity; }

// 			// * ============ MODIFIERS ============ * //

// 			void clear() { erase(begin(), end()); }

// 			iterator insert(iterator pos, const T& val) {
// 				if (m_capacity == 0)
// 				{
// 					reserve(1);
// 					m_allocator.construct(m_vector, val);
// 					m_size++;
// 					return begin();
// 				}
// 				if (m_capacity == m_size) {
// 					reserve(m_capacity << 1);
// 				}
// 				for (size_type dist = m_size; dist != static_cast<size_type>(pos - begin()); dist--) {
// 					m_allocator.construct(m_vector + dist, m_vector[dist - 1]);
// 				}
// 				m_allocator.construct(m_vector + static_cast<size_type>(pos - begin()), val);
// 				m_size++;
// 				return pos;
// 			}

// 			void insert (iterator pos, size_type n, const T& val) {
// 				size_type dist = static_cast<size_type>(pos - begin());
// 				if (m_size + n > max_size()) {
// 					throw OutOfLength();
// 				}
// 				if (dist > m_size)
// 					return ;
// 				if (m_size + n >= m_capacity)
// 					reserve(m_capacity * 2 + n);
// 				std::memmove(static_cast<void*>(m_vector + dist + n), static_cast<void*>(m_vector + dist), (size_t)(m_size - dist) * sizeof(T));
// 				for (size_type j = 0; j < n; ++j)
// 					m_allocator.construct(m_vector + dist + j, val);
// 				m_size += n;
// 			}

// 			template <class InIter>
//     		void insert (iterator pos, InIter first, InIter last, typename ft::enable_if<!std::is_integral<InIter>::val, InIter>::type* = 0) {
// 				size_type dist = static_cast<size_type>(pos - begin());
// 				size_type iterDistance = static_cast<size_type>(last - first);
// 				if (dist > m_size)
// 					return ;
// 				if (m_size + iterDistance >= m_capacity)
// 					this->reserve(m_size * 2 + iterDistance);
// 				std::memmove(static_cast<void*>(m_vector + dist + iterDistance), static_cast<void*>(m_vector + dist), (size_t)(m_size - dist) * sizeof(T));
// 				for (size_type j = 0; j < iterDistance; ++j)
// 					m_allocator.construct(m_vector + dist + j, *(first + j));
// 				m_size += iterDistance;
// 			}

// 			iterator erase(iterator pos) {
// 				difference_type diff = pos - begin();
// 				m_allocator.destroy(m_vector + diff);
// 				for (size_type dist = static_cast<size_type>(diff); dist < m_size - 1; dist++){
// 					m_allocator.construct(m_vector + dist, m_vector[dist + 1]);
// 				}
// 				m_size--;
// 				return pos;
// 			}

// 			iterator erase(iterator first, iterator last) {
// 				if (m_size == 0)
//             		return first;
//         		if (first != last) {
//             		size_type destr = last - begin();
// 					for (size_type dist = static_cast<size_type>(first - begin()); dist < destr; dist++) {
// 						m_allocator.destroy(m_vector + dist);
// 					}
// 					for (size_type dist = static_cast<size_type>(first - begin()); dist < m_size - (last - first); dist++) {
// 						m_allocator.construct(m_vector + dist, m_vector[dist + (last - first)]);
// 					}
// 					m_size -= (last - first);
// 				}
// 				else {
// 					erase(first);
// 				}
// 				return first;
// 				}

// 			void push_back(const value_type& val) {
// 				if (m_capacity == 0) { reserve(1); }
// 				else if (m_capacity == m_size) { reserve(m_capacity << 1); }
// 				m_vector[m_size] = val;
// 				m_size++;
// 			}

// 			void pop_back() { 
// 				if (m_size) { 
// 				m_size--;	
// 				m_allocator.destroy(m_vector + m_size);
// 				} 
// 			}

// 			void resize(size_type n) {
// 				if (m_capacity < n)
// 					reserve(n);
// 				while (n > m_size)
// 					push_back(0);
// 				while (n < m_size)
// 					pop_back();
// 			}

// 			void resize(size_type n, const T& val) {
// 				if (m_capacity < n)
// 					reserve(n);
// 				while (n > m_size)
// 					push_back(val);
// 				while (n < m_size)
// 					pop_back();
// 			}

// 			void swap (vector& X) {
// 				if (m_allocator != X.m_allocator) {
// 					ft::swap(m_allocator, X.m_allocator);
// 				}
// 				ft::swap(m_vector, X.m_vector);
// 				ft::swap(m_size, X.m_size);
// 				ft::swap(m_capacity, X.m_capacity);
// 			}

// 			class AllocationFailed : public std::exception	{
// 				const char* what() const throw() {
// 					return "Bad alloc exception";
// 				}
// 			};
// 			class OutOfRange : public std::exception	{
// 				const char* what() const throw() {
// 					return "Out of range exception";
// 				}
// 			};
// 			class OutOfLength : public std::exception	{
// 				const char* what() const throw() {
// 					return "Vector<T> too long";
// 				}
// 			};

// 			protected:
// 				bool Buy(size_type N) {
// 					First = 0, Last = 0, End = 0;
// 				}

// 			// void moveLeft(iterator first, iterator last) {
// 			// 	for (; first != end(); ++first, ++last) {
//             //         m_allocator.destroy(&(*first));
//             //         if (last < end())
//             //             m_allocator.construct(&(*(first)), *last);
//             //     }
// 			// }

// 			// void moveRight(iterator pos, size_type n) {
// 			// 	for (ft::pair<iterator, iterator> it(end() - 1, end()); it.second != pos; --it.first, --it.second) {
//             //         m_allocator.construct(&(*(it.first + n)), *it.first);
//             //         m_allocator.destroy(&(*it.first));
//             //     }
// 			// }
// 	};

// // * ============ NON MEMBER FUNATIONS ============ * //

// template<class T, class A>
// 	bool operator==(const vector<T, A>& lhs, const vector<T, A>& rhs) { 
// 		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

// template<class T, class A>
// 	bool operator!=(const vector<T, A>& lhs, const vector<T, A>& rhs) { return !(lhs == rhs); }

// template<class T, class A>
// 	bool operator<(const vector<T, A>& lhs, const vector<T, A>& rhs) { 
// 	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

// template<class T, class A>
// 	bool operator<=(const vector<T, A>& lhs, const vector<T, A>& rhs) { return !(rhs < lhs); }

// template<class T, class A>
// 	bool operator>(const vector<T, A>& lhs, const vector<T, A>& rhs) { return rhs < lhs; }

// template<class T, class A>
// 	bool operator>=(const vector<T, A>& lhs, const vector<T, A>& rhs) { return !(rhs > lhs); }

// template <class T, class Alloc>
// 	void swap (vector<T,Alloc>& lhs, vector<T,Alloc>&rhs) {	lhs.swap(rhs); }
// }

// #endif

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <stdexcept>
# include "../iterators/iterator.hpp"
# include "../iterators/vector_iterator.hpp"
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
			typedef ft::vector_iterator<value_type>			iterator;
			typedef ft::vector_iterator<value_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			// * ============ MEMBER FUNCTIONS ============ * //

			explicit vector(const A& alloc = allocator_type()) {
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

			template<typename Iter>
			void Construct(Iter first, Iter last, typename ft::enable_if<!std::is_integral<Iter>::value, Iter>::type* = 0) {
				Buy(0);
				insert(begin(), first, last);
			}

			template<typename Iter>
			void Construct(Iter first, Iter last, typename ft::enable_if<std::is_integral<Iter>::value, Iter>::type* = 0) {
				size_type N = (size_type)first;
				if (Buy(N)) {
					_last = Ufill(_first, N, (T)last);
				}
			}

			vector(const vector& X) {
				if (Buy(X.size()))
					_last = Ucopy(X.begin(), X.end(), _first);
			 }

			virtual ~vector() {
				Clear();
			}

			vector &operator=(const vector& X) {
				if (this == &X) { ; }
				else if (X.size() == 0) { Clear(); }
				else if (X.size() <= size()) {
					pointer Q = ft::copy(X.begin(), X.end(), _first);
					Destroy(Q, _last);
					_last = _first + X.size();
				}
				else if (X.size() <= capacity()) {
					const_iterator S = X.begin() + size();
					copy(X.begin(), S, _first);
					_last = Ucopy(S, X.end(), _last);
				}
				else {
					Destroy(_first, _last);
					_alloc.deallocate(_first, _end - _first);
					if (Buy(X.size()))
						_last = Ucopy(X.begin(), X.end(), _first);
				}
				return *this;
			}

			void reserve(size_type N) {
				if (max_size() < N) { Xlen(); }
				else if (capacity() < N) {
					pointer Q = _alloc.allocate(N, (void *)0);
					try {
						Ucopy(begin(), end(), Q);
					}
					catch(...) {
						_alloc.deallocate(Q, N);
						throw;
					}
					if (_first != 0) {
						Destroy(_first,_last);
						_alloc.deallocate(_first, _end - _first);
					}
					_end = Q + N;
					_last = Q + N;
					_first = Q;
				}
			}

			size_type capacity() const { return _first == 0 ? 0 : _end - _first; }			

			// * ============ ITERATORS ============ * //


			iterator begin(void) { return iterator(_first); }

			const_iterator begin(void) const { return const_iterator(_first); }

			iterator end(void) { return iterator(_last); }

			const_iterator end(void) const { return const_iterator(_last); }

			reverse_iterator rbegin(void) { return reverse_iterator(end()); }

			const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

			reverse_iterator rend(void) { return reverse_iterator(begin()); }

			const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

			void resize(size_type N) {
				resize(N, T());
			}

			void resize(size_type N, T X) {
				if (size() < N)
					insert(end(), N - size(), X);
				else if (N < size())
					erase(begin() + N, end());
			}

			size_type size() const { return _first == 0 ? 0 : _last - _first; }

			size_type max_size() const { return _alloc.max_size(); }

			bool empty() const { return size() == 0; }

			allocator_type get_allocator() const { return _alloc; }

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

			void push_back(const T& X) {
				insert(end(), X);
			}

			void pop_back() {
				erase(end() - 1);
			}

			template<typename Iter>
			void assign(Iter first, Iter last) {
				assign(first, last);
			}

			template<typename Iter>
			void assign(Iter first, Iter last, typename ft::enable_if<!std::numeric_limits<Iter>::is_integral>::type = 0) {
				assign((size_type)first, (T)last);
			}

			template<typename Iter>
			void assign(Iter first, Iter last, typename ft::enable_if<std::numeric_limits<Iter>::is_integral>::type = 0) {
				erase(begin(), end());
				insert(begin(), first, last);
			}

			void assign(size_type N, const T &X) {
				T Tx = X;
				erase(begin(), end());
				insert(begin(), N, Tx);
			}

			iterator insert(iterator pos, const T &X) {
				size_type offset = size() == 0 ? 0 : pos - begin();
				insert(pos, (size_type)1, X);
				return begin() + offset;
			}

			void insert(iterator pos, size_type M, const T &X) {
				T Tx = X;
				size_type N = capacity();
				if (M == 0) { ; }
				else if (max_size() - size() < M) { Xlen(); }
				else if (N < size() + M) {
					N = max_size() - N / 2 < N ? 0 : N + N / 2;
					if (N < size() + M) {
						N = size() + M;
					}
					pointer S = _alloc.allocate(N, (void *)0);
					pointer Q;
					try {
						Q = Ucopy(begin(), pos, S);
						Q = Ufill(Q, M, Tx);
						Ucopy(pos, end(), Q);
					}
					catch(...) {
						Destroy(S, Q);
						_alloc.deallocate(S, N);
						throw;
					}
					if (_first != 0) {
						Destroy(_first, _last);
						_alloc.deallocate(_first, _end - _first);
						_end = S + N;
						_last = S + size() + M;
						_first = S;
					}
				}
				else if ((size_type)(end() - pos) < M) {
					Ucopy(pos, end(), pos.base() + M);
					try {
						Ufill(_last, M - (end() - pos), Tx);
					}
					catch(...) {
						Destroy(pos.base() + M, _last + M);
						throw;
					}
					_last += M;
					ft::fill(pos, end() - M, Tx);
				}
				else {
					iterator Oend = end();
					_last = Ucopy(Oend - M, Oend, _last);
					ft::copy_backward(pos, Oend - M, Oend);
					ft::fill(pos, pos + M, Tx);
				}
			}

			template<typename Iter>
			void insert(iterator pos, Iter first, Iter last) {
				size_type M = ft::distance(first, last);
				size_type N = capacity();
				if (M == 0) { ; }
				else if (max_size() - size() < M) {
					Xlen();
				}
				else if (N < size() + M) {
					N = max_size() - N / 2 < N ? 0 : N + N / 2;
					if (N < size() + M)
						N = size() + M;
					pointer S = _alloc.allocate(N, (void *)0);
					pointer Q;
					try {
						Q = Ucopy(begin(), pos,S);
						Q = Ucopy(first, last, Q);
						Ucopy(pos, end(), Q);
					} 
					catch(...) {
						Destroy(S, Q);
						_alloc.deallocate(S, N);
						throw;
					}
					if (_first != 0) {
						Destroy(_first, _last);
						_alloc.deallocate(_first, _end - _first);
					}
					_end = S + N;
					_last = S + size() + M;
					_first = S;
				}
				else if ((size_type)(end() - pos) < M) {
					Ucopy(pos, end(), pos.base() + M);
					Iter Mid = first;
					ft::advance(Mid, end() - pos);
					try {
						Ucopy(Mid, last, _last);
					}
					catch(...) {
						Destroy(pos.base() + M, _last + M);
						throw;
					}
					_last += M;
					ft::copy(first, Mid, pos);
				}
				else if (0 < M) {
					iterator Oend = end();
					_last = Ucopy(Oend - M, Oend, _last);
					ft::copy_backward(pos, Oend - M, Oend);
					ft::copy(first, last, pos);
				}
			}


			iterator erase(iterator pos) {
				ft::copy(pos + 1, end(), pos);
				Destroy(_last - 1, _last);
				--_last;
				return pos;
			}

			iterator erase(iterator first, iterator last) {
				if (first != last) {
					pointer S = ft::copy(last, end(), first.base());
					Destroy(S, _last);
					_last = S;
				}
				return first;
			}

			void clear() { erase(begin(), end()); }

			bool Eq(const vector &X) const {
				return (size() == X.size() && ft::equal(begin(), end(), X.begin()));
			}

			bool Lt(const vector &X) const {
				return ft::lexicographical_compare(begin(), end(), X.begin(), X.end());
			}

			void swap(vector &X) {
				if (_alloc == X._alloc) {
					ft::swap(_first, X._first);
					ft::swap(_last, X._last);
					ft::swap(_end, X._end);
				}
				else {
					vector Ts = *this; 
					*this = X;
					X = Ts;
				}
			}

			protected:
				pointer _first, _last, _end;
				allocator_type _alloc;

				bool Buy(size_type N) { 
					_first = 0, _last = 0, _end = 0;
					if (N == 0)
						return false;
					else {
						_first = _alloc.allocate(N, (void *)0);
						_last = _first;
						_end = _first + N;
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