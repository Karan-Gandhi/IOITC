g++ ans.cpp -o ans
g++ brut.cpp -o brut
g++ gen.cpp -o gen

for((i = 1; ; ++i)); do # if they are same then will loop forever
    echo $i
    ./gen $i > int
    ./ans < int > out1
    ./brut < int > out2
    diff -w out1 out2 || break
    # diff -w <(./A < int) <(./B < int) || break
done