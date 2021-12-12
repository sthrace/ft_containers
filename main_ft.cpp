#include <vector>
#include <stack>
#include <iostream>
#include "stack.hpp"

int	main()
{
	std::stack<int> test;

	std::cout << "Stack initialized\n";
	
	// std::cout << test.top() << std::endl;
	std::cout << test.empty() << std::endl;
	std::cout << test.size() << std::endl;
	test.push(15);
	std::cout << test.top() << std::endl;
	std::cout << test.empty() << std::endl;
	std::cout << test.size() << std::endl;
	test.pop();
	// std::cout << test.top() << std::endl;
	std::cout << test.empty() << std::endl;
	std::cout << test.size() << std::endl;


	return 0;
}