cmake_minimum_required(VERSION 3.17)
project(multy_matrix)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)
add_executable (multy_matrix matrix.h Multys.h main.cpp)
target_link_libraries (Lab5 ${CMAKE_THREAD_LIBS_INIT})