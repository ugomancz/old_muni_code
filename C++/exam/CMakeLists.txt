cmake_minimum_required(VERSION 3.20)
project(exam)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(1a_tree 1a_tree.cpp)
add_executable(1b_expr 1b_expr.cpp)
add_executable(1c_trie 1c_trie.cpp)
