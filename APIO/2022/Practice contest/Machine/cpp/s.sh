g++ gen.cpp -o gen

for (( i = 0; ; i++ )); do
	echo $i
	./gen $i > int
	./machine < int
done