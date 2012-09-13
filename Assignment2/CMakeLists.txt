cmake_minimum_required(VERSION 2.6) 
project(ass2)

include(FindPkgConfig)
pkg_check_modules("gsl" REQUIRED)

include_directories(/usr/include/gsl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgsl -lgslcblas -lm")

add_executable(ass2 ass2.cpp x_intersection.cpp integrals.cpp)
target_link_libraries(ass2 ${GSL_LIBRARIES})
