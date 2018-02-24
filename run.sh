echo make
make
if [[ $? == 0 ]]; then
	echo "main"
	./main
fi