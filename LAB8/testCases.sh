#!/bin/bash
make; 
echo "----------FIFO----------"
cat testInput.txt | ./skeleton 10 1
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./skeleton 10 2
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./skeleton 10 3
echo "----------End Second Chance----------"

echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./skeleton 10 1
cat accesses.txt | ./skeleton 50 1
cat accesses.txt | ./skeleton 100 1
cat accesses.txt | ./skeleton 250 1
cat accesses.txt | ./skeleton 500 1
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./skeleton 10 2
cat accesses.txt | ./skeleton 50 2
cat accesses.txt | ./skeleton 100 2
cat accesses.txt | ./skeleton 250 2
cat accesses.txt | ./skeleton 500 2
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./skeleton 10 3
cat accesses.txt | ./skeleton 50 3
cat accesses.txt | ./skeleton 100 3
cat accesses.txt | ./skeleton 250 3
cat accesses.txt | ./skeleton 500 3
echo
make clean;
echo

