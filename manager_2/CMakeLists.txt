cmake_minimum_required(VERSION 3.15)
project(manager_2)

set(CMAKE_CXX_STANDARD 14)

find_library(PTHREAD_LIBRARY pthread)

add_executable(manager_2 main.c types.h protobufHandler.cpp protobufHandler.h queue.c queue.h)

target_link_libraries(manager_2 ${PTHREAD_LIBRARY})
