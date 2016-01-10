project(LibEventHttpServer)
cmake_minimum_required(VERSION 2.6)

include_directories(include)

add_executable(HttpServer
  src/main.cpp
)
