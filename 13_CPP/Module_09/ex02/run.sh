#!/bin/bash

numbers=$(shuf -i 1-${1:-10000} -n ${1:-4200})

numbers_str=$(echo $numbers | tr '\n' ' ')

# echo $numbers_str

./PmergeMe $numbers_str