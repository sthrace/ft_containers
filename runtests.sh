#!/bin/bash

if [ -n "$1" ]
then
	if [ $1 == 'clear' ]
	then
	rm test_* 2> /dev/null
	elif [ $1 == 'vector' ] || [ $1 == 'map' ] || [ $1 == 'stack' ] || [ $1 == 'set' ]
	then

	sed -i '' 's/#if 0/#if 1/' mytest_"$1".cpp
	clang++ -Wall -Werror -Wextra -std=c++98 mytest_"$1".cpp -o std
	./std > test_"$1"_std
	sed -i '' 's/#if 1/#if 0/' mytest_"$1".cpp
	clang++ -Wall -Werror -Wextra -std=c++98 mytest_"$1".cpp -o ft
	./ft > test_"$1"_ft
	diff test_"$1"_std test_"$1"_ft > test_"$1"_diff
	rm std
	rm ft
	else
	echo "Valid parameters are container name or clear"
	fi
else
echo "type -v for vector, -m for map, -st for stack, -s for set, -a for all containers or -c to cleanup"
fi