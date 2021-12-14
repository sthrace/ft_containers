#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <iterator>
# include <cstring>
# include <math.h>
# include "iterator.hpp"
# include "algorithm.hpp"

namespace ft
{
	template <class T, class A = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef A										allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*										pointer;
			typedef const T*								const_pointer;
			typedef ft::vector_iterator<value_type>			iterator;
			typedef ft::vector_iterator<value_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			

		protected:
			pointer 		m_vector;
			size_type		m_size;
			size_type		m_capacity;
			allocator_type	m_allocator;

		public:

			// * ============ MEMBER FUNCTIONS ============ * //

			explicit vector(const A& alloc = allocator_type()) : m_vector(NULL), m_size(0), m_capacity(0), m_allocator(alloc) {}

			explicit vector(size_type n, const value_type& val = value_type(),	const allocator_type& alloc = allocator_type()) : m_size(n), m_capacity(n), m_allocator(alloc) {
				m_vector = m_allocator.allocate(n);
				for (size_type i = 0; i < n; i++) {
					m_allocator.construct(m_vector + i, val);
				}
			}

			template <class InIter>
			vector(InIter first, typename std::enable_if<!std::numeric_limits<InIter>::is_integer, InIter>::type last, const allocator_type& alloc = allocator_type()) : m_allocator(alloc) {
				m_size = static_cast<size_type>(last - first);
				m_capacity = m_size;
				m_vector = m_allocator.allocate(m_capacity);
				for (size_type i = 0; i < m_size; i++)	{
					m_allocator.construct(m_vector + i, *(first + i));
				}
			}

			vector(const vector& X) {
				m_vector = m_allocator.allocate(0);
        		reserve(X.capacity());
				try
				{
					for (size_type i = 0; i < X.size(); i++)
						m_allocator.construct(m_vector + i, *(X.m_vector + i));
				}
				catch(...)
				{
					clear();
					m_allocator.deallocate(m_vector, m_capacity);
				}
			 }

			virtual ~vector() {
				m_allocator.destroy(m_vector);
				m_allocator.deallocate(m_vector, m_capacity);
			}

			vector& operator=(const vector &X) {
				if (this == &X)
					return *this;
				else if (X.size() == 0) { clear(); }
				else if (X.size() <= size()) {
					for (size_type i = 0; i < X.size(); i++)
						m_vector[i] = X.m_vector[i];
				}
				else if (X.size() <= capacity()) {
					for (size_type i = 0; i < X.size(); i++)
						m_vector[i] = X.m_vector[i];
				}
				else {
					m_allocator.deallocate(m_vector, m_capacity);
					m_vector = m_allocator.allocate(X.capacity());
					for (size_type i = 0; i < X.size(); i++)
						m_allocator.construct(m_vector + i, *(X.m_vector + i));
				}
				return *this;
			}

			void assign(size_type n, const T& val) {
				clear();
				m_allocator.deallocate(m_vector, m_capacity);
				m_vector = m_allocator.allocate(n);
				m_capacity = n;
				m_size = n;
				for (size_type dist = 0; dist < n; dist++)	{
					m_allocator.construct(m_vector + dist, val);
				}
			}

			template<class Iter>
			void assign(Iter first, typename std::enable_if<!std::numeric_limits<Iter>::is_integer,Iter>::type last)	{
				clear();
				m_allocator.deallocate(m_vector, m_capacity);
				size_type count = static_cast<size_type>(last - first);
				m_vector = m_allocator.allocate(count);
				m_capacity = count;
				m_size = count;
				size_type dist = 0;
				for (; first != last; first++)
				{
					m_allocator.construct(m_vector + dist, *first);
					dist++;
				}
			}

			allocator_type get_allocator(void) { return m_allocator; }
			
			// * ============ ELEMENT ACCESS ============ * //

			reference at(size_type idx) { 
				if (idx >= m_size)
					throw OutOfRange();
				return (*(begin() + idx)); 
			}
			const_reference at(size_type idx) const { 
				if (idx >= m_size)
					throw OutOfRange();
				return (*(begin() + idx)); 
			}
			reference operator[](size_type idx) { return (*(begin() + idx)); }

			const_reference operator[](size_type idx) const { return (*(begin() + idx)); }

			reference front() { return (*(begin())); }

			const_reference front() const { return (*(begin())); }

			reference back() { return (*(end() - 1)); }

			const_reference back() const { return (*(end() - 1)); }

			int* data() { 
				if (m_size) {
					return (int *)reinterpret_cast<std::ptrdiff_t>(&m_vector); 
				}
				return NULL;
			}
			
			// * ============ ITERATORS ============ * //

			iterator begin(void) { return iterator(m_vector); }

			const_iterator begin(void) const { return const_iterator(m_vector); }

			iterator end(void) { return iterator(m_vector + m_size); }

			const_iterator end(void) const { return const_iterator(m_vector + m_size); }

			reverse_iterator rbegin(void) { return reverse_iterator(end()); }

			const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

			reverse_iterator rend(void) { return reverse_iterator(begin()); }

			const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }
			
			// * ============ CAPACITY ============ * //

			bool empty(void) const { return m_size == 0; }

			size_type size(void) const { return m_size; }

			size_type max_size(void) const { return m_allocator.max_size(); }

			void reserve(size_type n) {
				if (n > max_size())
					throw AllocationFailed();
				if (n > m_capacity) {
					pointer temp = m_allocator.allocate(n);
					for (size_type i = 0; i < m_size; i++) {
						temp[i] = m_vector[i];
					}
					m_allocator.deallocate(m_vector, m_capacity);
					m_capacity = n;
					m_vector = temp;
				}
			}

			size_type capacity(void) const { return m_capacity; }

			// * ============ MODIFIERS ============ * //

			void clear() { erase(begin(), end()); }

			iterator insert(iterator pos, const T& val) {
				if (m_capacity == 0)
				{
					reserve(4);
					m_allocator.construct(m_vector + 0, val);
					m_size++;
					return begin();
				}
				if (m_capacity == m_size)
				{
					reserve(m_capacity << 1);
				}
				for (size_type i = m_size; i != static_cast<size_type>(pos - begin()); i--)
				{
					m_allocator.construct(m_vector + i, m_vector[i - 1]);
				}
				m_allocator.construct(m_vector + static_cast<size_type>(pos - begin()), val);
				m_size++;
				return pos;
			}

			// void insert(iterator pos, size_type n, const T& val) {
			// 	if (m_capacity == 0) {
			// 		reserve(n);
			// 		for (size_type i = 0; i < n; i++)
			// 			m_allocator.construct(m_vector + i, val);
			// 		m_size = n;
			// 		return begin();
			// 	}
			// 	if 
			// }

			// template<class InIter>
			// 	void insert(iterator pos, InIter first, InIter last)

			iterator erase(iterator pos) {
				difference_type diff = pos - begin();
				m_allocator.destroy(m_vector + diff);
				for (size_type dist = static_cast<size_type>(diff); dist < m_size - 1; dist++){
					m_allocator.construct(m_vector + dist, m_vector[dist + 1]);
				}
				m_size--;
				return pos;
			}

			iterator erase(iterator first, iterator last) {
				if (m_size == 0)
            		return first;
        		if (first != last) {
            		size_type destr = last - begin();
					for (size_type dist = static_cast<size_type>(first - begin()); dist < destr; dist++) {
						m_allocator.destroy(m_vector + dist);
					}
					for (size_type dist = static_cast<size_type>(first - begin()); dist < m_size - (last - first); dist++) {
						m_allocator.construct(m_vector + dist, m_vector[dist + (last - first)]);
					}
					m_size -= (last - first);
				}
				else {
					erase(first);
				}
				return first;
				}

			void push_back(const value_type& val) {
				if (m_capacity == 0) { reserve(1); }
				else if (m_capacity == m_size) { reserve(m_capacity << 1); }
				m_vector[m_size] = val;
				m_size++;
			}

			void pop_back() { if (m_size) { m_size--; } }

			void resize(size_type n) {
				if (m_capacity < n) { reserve(n); }
				for (size_type i = m_size; i < n; i++) {
					m_vector[i] = 0;
				}
				m_size = n;
			}

			void resize(size_type n, const T& val) {
				if (m_capacity < n) {
					reserve(n);
					for (size_type i = m_size; i < n; i++) {
						m_vector[i] = val;
					}
				}
				m_size = n;
			}

			class AllocationFailed : public std::exception	{
				const char* what() const throw() {
					return "Bad alloc exception";
				}
			};
			class OutOfRange : public std::exception	{
				const char* what() const throw() {
					return "Out of range exception";
				}
			};
	};
}

// * ============ NON MEMBER FUNATIONS ============ * //

template<class T, class A>
	bool operator==(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { 
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template<class T, class A>
	bool operator!=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return !(lhs == rhs); }

template<class T, class A>
	bool operator<(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { 
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template<class T, class A>
	bool operator<=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return !(rhs < lhs); }

template<class T, class A>
	bool operator>(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return rhs < lhs; }

template<class T, class A>
	bool operator>=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) { return !(rhs > lhs); }

//std::swap


#endif