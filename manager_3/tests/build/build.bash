#!/bin/bash

g++ --coverage ../src/main.test.c ../src/common/functions.test.c ../src/common/functions.test.h ../../common/functions.c ../../common/functions.h -o testing
./testing
lcov -t "testing" -o testing.info -c -d .
genhtml -o report testing.info

