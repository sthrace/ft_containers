#include <iostream>
#include "containers/stack.hpp"
#include <stack>

#if 1
#define _NAMESPACE std
#else
#define _NAMESPACE ft
#endif

void	operators_test(void)
{

}

void	pop_test(void)
{
	_NAMESPACE::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
}

void	push_test(void)
{
	_NAMESPACE::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
}

void	top_test(void)
{
	_NAMESPACE::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void	size_test(void)
{
	_NAMESPACE::stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

void	empty_test(void)
{
	_NAMESPACE::stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void	constructor_test(void)
{   
	ft::vector<int> myvector (2,200);        // vector with 2 elements

	_NAMESPACE::stack<int> first;                    // empty stack

	_NAMESPACE::stack<int,ft::vector<int> > third;  // empty stack using vector
	_NAMESPACE::stack<int,ft::vector<int> > fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
}

int	main()
{
	constructor_test();
	empty_test();
	size_test();
	top_test();
	push_test();
	pop_test();
	operators_test();
	return 0;
}