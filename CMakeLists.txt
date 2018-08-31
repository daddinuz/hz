cmake_minimum_required(VERSION 3.8)
project(hz CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(hz hz.cpp)
