cmake_minimum_required(VERSION 2.6) 
project(ass3)

include_directories("/usr/include/gsl")

set(GSL_LIBRARIES "-lgsl -lgslcblas -lm")

add_executable(ass3 ass3.cpp)
