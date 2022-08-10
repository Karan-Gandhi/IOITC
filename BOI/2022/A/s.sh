make

for (( i = 0; i < 720; i++ )); do
	echo $i
	./gen $i > in
	# make
	./a.out < in
done