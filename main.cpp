#include <vector>
#include <limits>
#include <stack>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <math.h>
#include "./containers/vector.hpp"

int	main()
{
	typedef ft::vector<int> project;
	typedef std::vector<int> real;

	real test1;
	project test;
	// long long limit = (long long)pow(2, 61) - 1;
	// ft::Vector<int> test2(3, 10);
	//ft::Vector<int> test3 = { 10, 20, 30 }; // C++11 and above

	std::cout << std::setw(20);
	std::cout << &test << "  |  " << &test1 << std::endl;
	std::cout << std::setw(20);
	std::cout << test.empty() << "  |  " << test1.empty() << std::endl;
	std::cout << std::setw(20);
	std::cout << test.size() << "  |  " << test1.size() << std::endl;
	std::cout << std::setw(20);
	std::cout << test.capacity() << "  |  " << test1.capacity() << std::endl;
	std::cout << std::setw(20);
	std::cout << test.max_size() << "  |  " << test1.max_size() << std::endl;

	// std::cout << test1[0] << std::endl;
	// test.insert(&test[6], 2);
	// test1.insert(&test[6], 3);
	test.push_back(5);
	test.push_back(4);
	test.insert(test.begin(), 2);
	// test.push_back(3);
	// test.push_back(2);
	// test.push_back(1);
	test1.push_back(5);
	test1.push_back(4);
	test1.push_back(3);
	test1.push_back(2);
	test1.push_back(1);
	// real::iterator		test1_begin = test1.begin();
	// project::iterator   test_begin = test.begin();
	// std::cout << "Iterator start: " << *test1_begin << std::endl;
	// test1.insert()
	// test.reserve(20);
	// test1.reserve(20);
	test.resize(1000);
	test1.resize(1000);
	std::cout << "AT " << test.at(0) << std::endl;
	std::cout << "[] " << test[0] << std::endl;
	std::cout << "DATA " << test.data() << std::endl;
	std::cout << "AT " << test1.at(0) << std::endl;
	std::cout << "[] " << test1[0] << std::endl;
	std::cout << "DATA " << test1.data() << std::endl;
	std::cout << std::setw(20);
	std::cout << test.capacity() << "  |  " << test1.capacity() << std::endl;
	std::cout << std::setw(20);
	std::cout << test.size() << "  |  " << test1.size() << std::endl;
	std::cout << std::setw(20);
	std::cout << &test << "  |  " << &test1 << std::endl;
	std::cout << test[0] << std::endl;
	std::cout << test1[0] << test1[1] << test1[2] << test1[3] << test1.at(4) << std::endl;


	return 0;
}