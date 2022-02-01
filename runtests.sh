#!/bin/bash

if [ -n "$1" ]
then
	if [ $1 = '-c' ]
	then
	rm test_* 2> /dev/null
	elif [ $1 = '-v' ] || [ $1 = '-m' ] || [ $1 = '-s' ] || [ $1 = '-st' ]
	then
	declare -A containers
	containers[-v]="vector" containers[-m]="map" containers[-s]="set" containers[-st]="stack"

	sed -i 's/#if 0/#if 1/' mytest_"${containers[$1]}".cpp
	clang++ -Wall -Werror -Wextra -std=c++98 mytest_"${containers[$1]}".cpp -o std
	./std > test_"${containers[$1]}"_std
	sed -i 's/#if 1/#if 0/' mytest_"${containers[$1]}".cpp
	clang++ -Wall -Werror -Wextra -std=c++98 mytest_"${containers[$1]}".cpp -o ft
	./ft > test_"${containers[$1]}"_ft
	diff test_"${containers[$1]}"_std test_"${containers[$1]}"_ft > test_"${containers[$1]}"_diff
	rm std
	rm ft
	else
	echo "Valid parameters are -m -s -st -v -c"
	fi
else
echo "type -v for vector, -m for map, -st for stack, -s for set, -a for all containers or -c to cleanup"
fi