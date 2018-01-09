#!/bin/sh
echo Hello World

gcc -c -Wall -Werror -fpic foo.c -g
gcc -shared -o libfoo.so foo.o
g++ -L./ -Wall -o test mainCpp.cpp -lfoo -g
