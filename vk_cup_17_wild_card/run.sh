for i in `seq 1 9`;
do
    ./ez < 0$i.txt | head -n 1
done
./ez < 10.txt | head -n 1
