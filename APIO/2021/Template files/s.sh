for((i = 1; ; ++i)); do
    echo $i
    ./gen $i > int
    ./ans < int > out1
    ./brut < int > out2
    diff -w out1 out2 || break
    # diff -w <(./A < int) <(./B < int) || break
done