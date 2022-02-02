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

void	get_allocator_test(void)
{
	_NAMESPACE::set<int> myset;
	int * p;
	unsigned int i;

	// allocate an array of 5 elements using myset's allocator:
	p=myset.get_allocator().allocate(5);

	// assign some values to array
	for (i=0; i<5; i++) p[i]=(i+1)*10;

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	myset.get_allocator().deallocate(p,5);
}

void	equal_range_test(void)
{
	_NAMESPACE::set<int> myset;

	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

	_NAMESPACE::pair<_NAMESPACE::set<int>::const_iterator, _NAMESPACE::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}

void	lower_upper_bound_test(void)
{
	_NAMESPACE::set<int> myset;
	_NAMESPACE::set<int>::iterator itlow,itup;

	for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itlow=myset.lower_bound (30);                //       ^
	itup=myset.upper_bound (60);                 //                   ^

	myset.erase(itlow,itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (_NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	count_test(void)
{
	_NAMESPACE::set<int> myset;

	// set some initial values:
	for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

	for (int i=0; i<10; ++i)
	{
		std::cout << i;
		if (myset.count(i)!=0)
		std::cout << " is an element of myset.\n";
		else
		std::cout << " is not an element of myset.\n";
	}
}

void	find_test(void)
{
	_NAMESPACE::set<int> myset;
	_NAMESPACE::set<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

	it=myset.find(20);
	myset.erase (it);
	myset.erase (myset.find(40));

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	value_comp_test(void)
{
	_NAMESPACE::set<int> myset;

	_NAMESPACE::set<int>::value_compare mycomp = myset.value_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	int highest=*myset.rbegin();
	_NAMESPACE::set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';
}

void	key_comp_test(void)
{
	_NAMESPACE::set<int> myset;
	int highest;

	_NAMESPACE::set<int>::key_compare mycomp = myset.key_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	highest=*myset.rbegin();
	_NAMESPACE::set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';
}

void	clear_test(void)
{
	_NAMESPACE::set<int> myset;

	myset.insert (100);
	myset.insert (200);
	myset.insert (300);

	std::cout << "myset contains:";
	for (_NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myset.clear();
	myset.insert (1101);
	myset.insert (2202);

	std::cout << "myset contains:";
	for (_NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	swap_test(void)
{
	int myints[]={12,75,10,32,20,25};
	_NAMESPACE::set<int> first (myints,myints+3);     // 10,12,75
	_NAMESPACE::set<int> second (myints+3,myints+6);  // 20,25,32

	first.swap(second);

	std::cout << "first contains:";
	for (_NAMESPACE::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (_NAMESPACE::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	erase_test(void)
{
	_NAMESPACE::set<int> myset;
	_NAMESPACE::set<int>::iterator it;

	// insert some values:
	for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

	it = myset.begin();
	++it;                                         // "it" points now to 20

	myset.erase (it);

	myset.erase (40);

	it = myset.find (60);
	myset.erase (it, myset.end());

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	insert_test(void)
{
	_NAMESPACE::set<int> myset;
	_NAMESPACE::set<int>::iterator it;
	_NAMESPACE::pair<_NAMESPACE::set<int>::iterator,bool> ret;

	// set some initial values:
	for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

	ret = myset.insert(20);               // no new element inserted

	if (ret.second==false) it=ret.first;  // "it" now points to element 20

	myset.insert (it,25);                 // max efficiency inserting
	myset.insert (it,24);                 // max efficiency inserting
	myset.insert (it,26);                 // no max efficiency inserting

	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset.insert (myints,myints+3);

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	max_size_test(void)
{
	int i;
	_NAMESPACE::set<int> myset;

	if (myset.max_size()>1000)
	{
		for (i=0; i<1000; i++) myset.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	}
	else std::cout << "The set could not hold 1000 elements.\n";
}

void	size_test(void)
{
	_NAMESPACE::set<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; ++i) myints.insert(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.erase(5);
	std::cout << "3. size: " << myints.size() << '\n';
}

void	empty_test(void)
{
	_NAMESPACE::set<int> myset;

	myset.insert(20);
	myset.insert(30);
	myset.insert(10);

	std::cout << "myset contains:";
	while (!myset.empty())
	{
		std::cout << ' ' << *myset.begin();
		myset.erase(myset.begin());
	}
	std::cout << '\n';
}

void	rbegin_rend_test(void)
{
	int myints[] = {21,64,17,78,49};
	_NAMESPACE::set<int> myset (myints,myints+5);

	_NAMESPACE::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}

void	begin_end_test(void)
{
	int myints[] = {75,23,65,42,13};
	_NAMESPACE::set<int> myset (myints,myints+5);

	std::cout << "myset contains:";
	for (_NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
}

void	assignator_test(void)
{
	int myints[]={ 12,82,37,64,15 };
	_NAMESPACE::set<int> first (myints,myints+5);   // set with 5 ints
	_NAMESPACE::set<int> second;                    // empty set

	second = first;                          // now second contains the 5 ints
	first = _NAMESPACE::set<int>();                 // and first is empty

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
}

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
	unsigned int start_time =  clock();
	constructor_test();
	assignator_test();
	begin_end_test();
	rbegin_rend_test();
	empty_test();
	size_test();
	max_size_test();
	insert_test();
	erase_test();
	swap_test();
	clear_test();
	key_comp_test();
	value_comp_test();
	find_test();
	count_test();
	lower_upper_bound_test();
	equal_range_test();
	get_allocator_test();
	unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    std::cout << " performance time is: " << search_time << std::endl;

	return 0;
}
