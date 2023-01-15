cmake_minimum_required(VERSION 3.22)
project(SharedLib)

set(CMAKE_CXX_STANDARD 20)

add_library(mylib SHARED triangle_area.h triangle_area.cpp)
add_executable(main main.cpp)
target_link_libraries(main mylib)
