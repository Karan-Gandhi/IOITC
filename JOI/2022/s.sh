for((i = 1; ; ++i)); do # if they are same then will loop forever
    echo $i
    ./gen.exe $i > int
    ./ans.exe < int > out1
    ./brut.exe < int > out2
    diff -w out1 out2 || break
    # diff -w <(./A < int) <(./B < int) || break
done