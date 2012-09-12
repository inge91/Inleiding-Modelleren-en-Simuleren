cmake_minimum_required(VERSION 2.6) 
project(ass2)

# C++0x support
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

add_executable(ass2 ass2.cpp x_intersection.cpp integrals.cpp)
