#!/bin/bash

g++ --coverage ../main.test.c ../common/functions.test.c ../common/functions.test.h ../../common/functions.c ../../common/functions.h -o testing
./testing
lcov -t "testing" -o testing.info -c -d .
genhtml -o report testing.info

