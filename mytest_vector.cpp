#include <vector>
#include "./containers/vector.hpp"
#include <iostream>

#if 0
#define _NAMESPACE std
#else
#define _NAMESPACE ft
#endif

void	non_member_swap_test(void)
{
	_NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
	_NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (_NAMESPACE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (_NAMESPACE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	operators_test(void)
{
	_NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
	_NAMESPACE::vector<int> bar (2,200);   // two ints with a value of 200

	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo < bar) std::cout << "foo is less than bar\n";
	if (foo > bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

void	get_alloc_test(void)
{
	_NAMESPACE::vector<int> myvector;
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	// destroy and deallocate:
	for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p,5);
}

void	clear_test(void)
{
	_NAMESPACE::vector<int> myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.clear();
	myvector.push_back (1101);
	myvector.push_back (2202);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	swap_test(void)
{
	_NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
	_NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
}

void	erase_test(void)
{
	_NAMESPACE::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);

	// erase the 6th element
	myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	// myvector.erase (myvector.begin(),myvector.begin()+3);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	insert_test(void)
{
	_NAMESPACE::vector<int> myvector (3,100);
	_NAMESPACE::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	_NAMESPACE::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	pop_back_test(void)
{
	_NAMESPACE::vector<int> myvector;
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << '\n';
}

void	push_back_test(void)
{
	_NAMESPACE::vector<int> myvector;

	myvector.push_back (1);
	myvector.push_back (10);
	myvector.push_back (100);
	myvector.push_back (1000);
	myvector.push_back (10000);

	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
}

void	assign_test(void)
{
	_NAMESPACE::vector<int> first;
	_NAMESPACE::vector<int> second;
	_NAMESPACE::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	_NAMESPACE::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
}

void	data_test(void)
{
	_NAMESPACE::vector<int> myvector (5);

	int* p = myvector.data();

	*p = 10;
	++p;
	*p = 20;
	p[2] = 100;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	back_test(void)
{
	_NAMESPACE::vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back ( myvector.back() - 1 );
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size() ; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}

void	front_test(void)
{
	_NAMESPACE::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void	at_test(void)
{
	_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}

void	ref_by_index_test(void)
{
	_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized elements

	_NAMESPACE::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}

void	reserve_test(void)
{
	_NAMESPACE::vector<int>::size_type sz;

	_NAMESPACE::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
		sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}

	_NAMESPACE::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
		sz = bar.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void	empty_test(void)
{
	_NAMESPACE::vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++) myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	std::cout << "total: " << sum << '\n';

}

void	capacity_test(void)
{
	_NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	// std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}

void	resize_test(void)
{
	_NAMESPACE::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i=0; i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	max_size_test(void)
{
	_NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << myvector.size() << "\n";
	// std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n";
}

void	size_test(void)
{
	_NAMESPACE::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
}

void	rend_test(void)
{
	_NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

	_NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (_NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	rbegin_test(void)
{
	_NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	_NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit != myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (_NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	end_test(void)
{
	_NAMESPACE::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (_NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

}

void	begin_test(void)
{
	_NAMESPACE::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (_NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void	assignator_test(void)
{
	_NAMESPACE::vector<int> foo (3,0);
	_NAMESPACE::vector<int> bar (5,0);

	bar = foo;
	foo = _NAMESPACE::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void	constructor_test(void)
{
	_NAMESPACE::vector<int> first;                                // empty vector of ints
	_NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
	_NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
	_NAMESPACE::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	_NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (_NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

int	main()
{
	constructor_test();
	assignator_test();
	begin_test();
	end_test();
	rbegin_test();
	rend_test();
	size_test();
	max_size_test();
	resize_test();
	capacity_test();
	empty_test();
	reserve_test();
	ref_by_index_test();
	at_test();
	front_test();
	back_test();
	data_test();
	assign_test();
	push_back_test();
	pop_back_test();
	insert_test();
	erase_test();
	swap_test();
	clear_test();
	get_alloc_test();
	operators_test();
	non_member_swap_test();
	return 0;
}