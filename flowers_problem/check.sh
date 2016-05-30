#!/bin/bash
for ((i = 1; i <= 10000; i++))
do
    echo "test $i"
    ./gen $i $i > inp
    ./dk_bad_div > n2.out
    ./dk_nlogn > nlogn.out
    diff -w n2.out nlogn.out
    cat n2.out
done
