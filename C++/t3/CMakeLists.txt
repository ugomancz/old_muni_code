cmake_minimum_required(VERSION 3.19)
project(t3)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(tree tree.cpp)
add_executable(bplus bplus.cpp)
add_executable(linalg linalg.cpp)
add_executable(lisp lisp.cpp)
