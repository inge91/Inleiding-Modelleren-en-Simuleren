cmake_minimum_required(VERSION 2.6) 
project(ass2)

include_directories("/usr/include/gsl")

set(GSL_LIBRARIES "-lgsl -lgslcblas -lm")

add_executable(ass2 ass2.cpp x_intersection.cpp integrals.cpp)
target_link_libraries(ass2 ${GSL_LIBRARIES})
