for((i=0;i<1000;i++))
do
    echo Test $i
    ./gen > inp
    head -n 1 inp
    ./sonka < inp > sonka_ans
    ./brute < inp > brute_ans
    diff sonka_ans brute_ans
done
