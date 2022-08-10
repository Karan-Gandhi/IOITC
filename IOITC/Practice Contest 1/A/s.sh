for((i = 1; ; ++i)); do
    echo $i
    ./gen $i > int
    ./grader < int
done