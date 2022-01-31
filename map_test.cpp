#include <map>
#include "./containers/map.hpp"
#include <iostream>

#if 0
#define _NAMESPACE std
#else
#define _NAMESPACE ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

// void	assignator_test(void)
// {
// 	std::map<char,int> first;
// 	std::map<char,int> second;

// 	first['x']=8;
// 	first['y']=16;
// 	first['z']=32;

// 	second=first;                // second now contains 3 ints
// 	first=std::map<char,int>();  // and first is now empty

// 	std::cout << "Size of first: " << first.size() << '\n';
// 	std::cout << "Size of second: " << second.size() << '\n';
// }

void	constructor_test(void)
{
	_NAMESPACE::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	first['e']=170;

	// if (first.begin() == first.end())
	// 	std::cout << "Iterators are equal" << std::endl;
	// else
	// 	std::cout << "Iterators are different" << std::endl;
	// std::cout << first['a'] << std::endl;
	// std::cout << first['b'] << std::endl;
	// std::cout << first['c'] << std::endl;
	// std::cout << first['d'] << std::endl;

	// std::cout << &first << std::endl;
	// std::cout << first.size() << std::endl;
	// std::cout << first.count('a') << std::endl;
	// std::cout << first.count('b') << std::endl;
	// std::cout << first.count('c') << std::endl;
	// std::cout << first.count('d') << std::endl;
	// _NAMESPACE::map<char,int> second (first.begin(),first.end());
	// std::cout << second['a'] << std::endl;
	// std::cout << second['w'] << std::endl;

	_NAMESPACE::map<char,int> third (first);

	// _NAMESPACE::map<char,int,classcomp> fourth;                 // class as Compare

	// bool(*fn_pt)(char,char) = fncomp;
	// _NAMESPACE::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
}

int		main()
{
	constructor_test();
	// assignator_test();
	return 0;
}