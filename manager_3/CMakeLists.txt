cmake_minimum_required(VERSION 3.15)
project(manager_3)

set(CMAKE_CXX_STANDARD 14)

INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER ../message.proto)
ADD_LIBRARY(proto3 ${PROTO_HEADER} ${PROTO_SRC})
TARGET_LINK_LIBRARIES(proto3)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

find_library(PTHREAD_LIBRARY pthread)
add_executable(manager_3 main.c io/protobufHandler.cpp io/protobufHandler.h common/queue.c common/queue.h common/types.h io/reader.c io/reader.h parser.c parser.h io/writer.c io/writer.h strategy.c strategy.h common/functions.c common/functions.h io/fileWriter.c io/fileWriter.h system.c system.h)

add_executable(testing tests/src/main.test.c tests/src/common/functions.test.c tests/src/common/functions.test.h io/protobufHandler.cpp io/protobufHandler.h common/queue.c common/queue.h common/types.h io/reader.c io/reader.h parser.c parser.h io/writer.c io/writer.h strategy.c strategy.h common/functions.c common/functions.h io/fileWriter.c io/fileWriter.h system.c system.h)

TARGET_LINK_LIBRARIES(manager_3 proto3 ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(testing proto3 ${PROTOBUF_LIBRARY})
target_link_libraries(manager_3 ${PTHREAD_LIBRARY})
target_link_libraries(testing ${PTHREAD_LIBRARY})
