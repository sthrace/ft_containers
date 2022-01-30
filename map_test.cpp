#include <map>
#include "./containers/map.hpp"
#include <iostream>

#if 1
#define _NAMESPACE std
#else
#define _NAMESPACE ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

void	constructor_test(void)
{
	_NAMESPACE::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	_NAMESPACE::map<char,int> second (first.begin(),first.end());

	_NAMESPACE::map<char,int> third (second);

	_NAMESPACE::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	_NAMESPACE::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
}

int		main()
{
	constructor_test();
	return 0;
}