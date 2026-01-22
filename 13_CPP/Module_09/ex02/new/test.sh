#!/bin/bash

export CXXFLAGS="-DCOMPARISON_COUNT=1"

max_comp_vec=0
max_comp_deq=0
min_comp_vec=999999
min_comp_deq=999999
sum_comp_vec=0
sum_comp_deq=0
count=0

br="\033[1;31m"
bg="\033[1;32m"
by="\033[1;33m"
rst="\033[0m"

make > /dev/null 2>&1

for i in {1..10}; do
    numbers=$(shuf -i 1-${1:-10000} -n ${1:-4200})
    numbers_str=$(echo $numbers | tr '\n' ' ')

    output=$(./PmergeMe $numbers_str)

    comp_max=$(echo "$output" | grep "Max allowed comparisons:" | awk '{print $NF}')
    comp_vec=$(echo "$output" | grep "Comparisons vector:" | awk '{print $NF}')
    comp_deq=$(echo "$output" | grep "Comparisons deque" | awk '{print $NF}')

    max_comp_vec=$((comp_vec > max_comp_vec ? comp_vec : max_comp_vec))
    max_comp_deq=$((comp_deq > max_comp_deq ? comp_deq : max_comp_deq))
    min_comp_vec=$((comp_vec < min_comp_vec ? comp_vec : min_comp_vec))
    min_comp_deq=$((comp_deq < min_comp_deq ? comp_deq : min_comp_deq))
    sum_comp_vec=$((sum_comp_vec + comp_vec))
    sum_comp_deq=$((sum_comp_deq + comp_deq))
    count=$((count + 1))
done

avg_comp_vec=$((sum_comp_vec / count))
avg_comp_deq=$((sum_comp_deq / count))

################################################################################
echo ""
echo -e "After ${by}10${rst} runs with ${by}${1:-4200}${rst} numbers:"
echo -e "Maximum allowed comparisons: ${by}$comp_max${rst}"

# Vector colors
vec_max_c=$((max_comp_vec <= comp_max ? 2 : 1))
vec_min_c=$((min_comp_vec <= comp_max ? 2 : 1))
vec_avg_c=$((avg_comp_vec <= comp_max ? 2 : 1))
vec_max_col=$([ $vec_max_c -eq 1 ] && echo "$br" || echo "$bg")
vec_min_col=$([ $vec_min_c -eq 1 ] && echo "$br" || echo "$bg")
vec_avg_col=$([ $vec_avg_c -eq 1 ] && echo "$br" || echo "$bg")

# Deque colors
deq_max_c=$((max_comp_deq <= comp_max ? 2 : 1))
deq_min_c=$((min_comp_deq <= comp_max ? 2 : 1))
deq_avg_c=$((avg_comp_deq <= comp_max ? 2 : 1))
deq_max_col=$([ $deq_max_c -eq 1 ] && echo "$br" || echo "$bg")
deq_min_col=$([ $deq_min_c -eq 1 ] && echo "$br" || echo "$bg")
deq_avg_col=$([ $deq_avg_c -eq 1 ] && echo "$br" || echo "$bg")

echo "---------------------------------"
echo -e "${by}Vector${rst} - Max: ${vec_max_col}$max_comp_vec${rst}, Min: ${vec_min_col}$min_comp_vec${rst}, Avg: ${vec_avg_col}$avg_comp_vec${rst}"
echo -e "${by}Deque${rst}  - Max: ${deq_max_col}$max_comp_deq${rst}, Min: ${deq_min_col}$min_comp_deq${rst}, Avg: ${deq_avg_col}$avg_comp_deq${rst}"
echo ""

make fclean > /dev/null 2>&1
