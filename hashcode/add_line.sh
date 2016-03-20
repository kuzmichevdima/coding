function get {
       echo $str | awk '{print $1;}'

   }

str=$(wc $1)
#echo $str
str2=$(get)
echo $str2 > fucking_file.txt
cat $1 >> fucking_file.txt
cp fucking_file.txt $1
rm fucking_file.txt
