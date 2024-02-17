#!/bin/bash
# cat /dev/random | head -c <bytecount>
cat /dev/random | head -c 100000000 > file4.txt
cat /dev/random | head -c 10000000000 > file5.txt

