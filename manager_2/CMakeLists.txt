cmake_minimum_required(VERSION 3.15)
project(manager_2)

set(CMAKE_CXX_STANDARD 14)

INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER ../message.proto)
ADD_LIBRARY(proto3 ${PROTO_HEADER} ${PROTO_SRC})
TARGET_LINK_LIBRARIES(proto3)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

find_library(PTHREAD_LIBRARY pthread)

add_executable(manager_2 main.c functions.c functions.h reporter.c reporter.h strategy.c strategy.h writer.c writer.h types.h protobufHandler.cpp protobufHandler.h queue.c queue.h reader.c reader.h parser.c parser.h)

TARGET_LINK_LIBRARIES(manager_2 proto3 ${PROTOBUF_LIBRARY})
target_link_libraries(manager_2 ${PTHREAD_LIBRARY})
