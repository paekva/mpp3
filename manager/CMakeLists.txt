cmake_minimum_required(VERSION 3.15)
project(manager)

set(CMAKE_CXX_STANDARD 14)

INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER ../message.proto)
ADD_LIBRARY(proto3 ${PROTO_HEADER} ${PROTO_SRC})
TARGET_LINK_LIBRARIES(proto3)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

find_library(PTHREAD_LIBRARY pthread)

add_executable(manager main.cpp reader.cpp reader.h types.h parser.cpp parser.h functions.cpp functions.h)

TARGET_LINK_LIBRARIES(manager proto3 ${PROTOBUF_LIBRARY})
target_link_libraries(manager ${PTHREAD_LIBRARY})
