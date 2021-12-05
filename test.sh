#!/bin/sh

cc test.c match.c -ggdb -Wall -Wpedantic -o ./test
./test
rm ./test
