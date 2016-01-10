project(LibEventHttpServer)
cmake_minimum_required(VERSION 2.6)

include_directories(include

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(HttpServer
  src/main.cpp
)
