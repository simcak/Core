#!/bin/bash

# Run the tester ~10 times with increasing number sizes
for size in 1 2 3 13 21 55 100 543 1042 2048 3000 5432; do
	echo "=========================================="
	echo "Running with $size numbers"
	echo "=========================================="
	./test.sh $size
done
