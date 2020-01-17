#!/bin/bash
./../../cmake-build-debug/testing
lcov -t "testing" -o testing.info -c -d .
genhtml -o report testing.info

