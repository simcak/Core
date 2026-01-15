#!/bin/bash

numbers=$(shuf -i 1-${1:-10000} -n ${1:-4200})

numbers_str=$(echo $numbers | tr '\n' ' ')

if [ "${2:-0}" == "1" ]; then
	echo -e "$numbers_str\n"
fi

./PmergeMe $numbers_str