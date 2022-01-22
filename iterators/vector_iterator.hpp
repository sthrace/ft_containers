#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

namespace ft {
	template<typename T>
	class vector_iterator : public ft::iterator<random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

	protected:
		pointer ptr;

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

		pointer	base() const {
			return ptr;
		}
	};
}

#endif