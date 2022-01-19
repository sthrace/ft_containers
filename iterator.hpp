#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <memory>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class C, class T, class Dist = std::ptrdiff_t, class Pt = T*, class Rt = T&>
	struct iterator {
		typedef C		iterator_category;
		typedef T		value_type;
		typedef Dist	difference_type;
		typedef Pt		pointer;
		typedef Rt		reference;
	};

	template<class iter>
	struct iterator_traits {
		typedef typename iter::iterator_category	iterator_category;
		typedef typename iter::value_type			value_type;
		typedef typename iter::difference_type		difference_type;
		typedef typename iter::pointer				pointer;
		typedef typename iter::reference			reference;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef ft::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef ft::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		};

	template <typename T>
	class vector_iterator : public ft::iterator<random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

		protected:
			pointer	ptr;

		public:

			vector_iterator(void) {}
			vector_iterator(pointer ptr) : ptr(ptr) {}
			vector_iterator(const vector_iterator &source) { *this = source; }
			virtual ~vector_iterator() {}

			vector_iterator &operator=(const vector_iterator &source) {
				if (this != &source) {
					ptr = source.ptr;
				}
				return *this;
			}

			vector_iterator &operator++() {
				ptr++;
				return *this;
			}

			vector_iterator operator++(int) { 
				vector_iterator temp(*this);
				ptr++;
				return temp;
			}

			vector_iterator &operator--() {
				ptr--;
				return *this;
			}

			vector_iterator operator--(int) { 
				vector_iterator temp(*this);
				ptr--;
				return temp;
			}

			vector_iterator operator+(difference_type n) { 
				vector_iterator temp(*this);
				return (temp += n); 
			}

			vector_iterator operator-(difference_type n) { 
				vector_iterator temp(*this);
				return (temp -= n);  
			}

			vector_iterator &operator+=(difference_type n) {
				ptr += n;
				return *this; 
			}

			vector_iterator &operator-=(difference_type n) {
				ptr -= n;
				return *this; 
			}
			
			reference &operator*() { return *ptr; }
			const reference &operator*() const { return *ptr; }
			pointer operator->() { return ptr; }
			const pointer operator->() const { return ptr; }
			reference operator[](difference_type idx) { return *(ptr + idx); }
			const reference operator[](difference_type idx) const { return *(ptr + idx); }

			bool operator==(const vector_iterator& rhs) { return ptr == rhs.ptr; }
			bool operator!=(const vector_iterator& rhs) { return ptr != rhs.ptr; }
			bool operator>(const vector_iterator& rhs) { return ptr > rhs.ptr; }
			bool operator>=(const vector_iterator& rhs) { return ptr >= rhs.ptr; }
			bool operator<(const vector_iterator& rhs) { return ptr < rhs.ptr; }
			bool operator<=(const vector_iterator& rhs) { return ptr <= rhs.ptr; }

			difference_type operator-(vector_iterator const &source) const {
				return (this->ptr - source.ptr);
			}
	};
		
	template <class Iter>
	class reverse_iterator {
		typedef Iter								iterator_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef	typename Iter::difference_type		difference_type;
		typedef	typename Iter::pointer				pointer;
		typedef	typename Iter::reference			reference;

		protected:
			iterator_type		current;

		public:
			reverse_iterator(void) {}

			explicit reverse_iterator(Iter base) : current(base) {}

			template<class U>
				reverse_iterator(const U& X) : current(X.base()) {}

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

			reverse_iterator operator+(difference_type n) {
				return reverse_iterator<Iter>(current - n);
			}

			const reverse_iterator operator+(difference_type n) const {
				return reverse_iterator<Iter>(current - n);
			}

			reverse_iterator operator-=(difference_type n) {
				current += n;
				return *this;
			}

			const reverse_iterator operator-(difference_type n) const {
				return reverse_iterator<Iter>(current + n);
			}

			reverse_iterator operator-(difference_type n) {
				return reverse_iterator<Iter>(current + n);
			}

			reverse_iterator operator[](difference_type n) {
				return *(this + n);
			}

			const reverse_iterator operator[](difference_type n) const {
				return *(this + n);
			}

	};
}

#endif