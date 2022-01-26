#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "vector_iterator.hpp"
# include "map_iterator.hpp"

namespace ft {
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
}

#endif