#!/bin/bash

# Run the tester ~10 times with increasing number sizes
for size in '   1' '   3' '   5' '  13' '  21' '  42' '  55' ' 100' ' 543' '1042' '2048' '3000'; do
	echo "====================================="
	echo "|     Running with $size numbers     |"
	echo "====================================="
	./t_comp.sh $size
done
