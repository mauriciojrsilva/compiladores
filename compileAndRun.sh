#!/bin/bash
cmake CMakeLists.txt
make
if [[ -z "$1" ]]; then
	./main
else
	cat $1 | ./main
fi
