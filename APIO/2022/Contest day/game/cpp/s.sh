g++ gen.cpp -o gen

for((i = 1; ; ++i)); do
    echo $i
    ./gen $i > int
    ./game < int > out1
    ./brut < int > out2
    diff -w out1 out2 || break
    # diff -w <(./A < int) <(./B < int) || break
done