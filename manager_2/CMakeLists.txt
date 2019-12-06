cmake_minimum_required(VERSION 3.15)
project(manager_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(manager_2 main.c types.h protobufHandler.cpp protobufHandler.h queue.c queue.h)