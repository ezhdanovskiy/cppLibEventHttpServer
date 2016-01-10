project(LibEventHttpServer)
cmake_minimum_required(VERSION 2.6)

set(BIN_NAME HttpServer)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#find_package(event REQUIRED)

add_executable(${BIN_NAME}
  src/HttpServer.cpp
  src/main.cpp
)
TARGET_LINK_LIBRARIES(${BIN_NAME} pthread event)
