cmake_minimum_required(VERSION 3.5)

project(testCurl2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(curl /usr/lib/x86-linux-gnu/curl)
add_executable(testCurl2 main.cpp)

