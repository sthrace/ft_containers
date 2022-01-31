#include <set>
#include "./containers/set.hpp"
#include <iostream>

#if 0
#define _NAMESPACE std
#else
#define _NAMESPACE ft
#endif

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

void	constructor_test(void)
{
	_NAMESPACE::set<int> first;                           // empty set of ints

	int myints[]= {10,20,30,40,50};
	_NAMESPACE::set<int> second (myints,myints+5);        // range

	_NAMESPACE::set<int> third (second);                  // a copy of second

	_NAMESPACE::set<int> fourth (second.begin(), second.end());  // iterator ctor.

	_NAMESPACE::set<int,classcomp> fifth;                 // class as Compare

	bool(*fn_pt)(int,int) = fncomp;
	_NAMESPACE::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare
}

int		main()
{
	constructor_test();
	// assignator_test();
	// begin_end_test();
	// rbegin_rend_test();
	// empty_test();
	// size_test();
	// max_size_test();
	// operator_index_test();
	// insert_test();
	// erase_test();
	// swap_test();
	// clear_test();
	// key_comp_test();
	// value_comp_test();
	// find_test();
	// count_test();
	// lower_upper_bound_test();
	// equal_range_test();
	// get_allocator_test();

	return 0;
}