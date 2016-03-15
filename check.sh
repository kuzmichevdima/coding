#!/bin/bash
echo arg1:$1
echo arg2:$2
for ((i = $1; i <= $2; i++))
do
    echo "test $i"
    if test $i -lt 10 
    then
        name="0$i"
    else
        name="$i"
    fi
    output_name=$name".a"
    cp $3/$name inp
    ./$4 > outp
    diff -w outp $3/$output_name
    cat outp
    #echo "right answer"
    #cat $3/$output_name
    #echo ""
done
