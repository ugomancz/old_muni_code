cmake_minimum_required(VERSION 3.19)
project(09)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(g1_circular g1_circular.cpp)
add_executable(g2_buffer g2_buffer.cpp)
add_executable(g3_stats g3_stats.cpp)
add_executable(g4_sparse g4_sparse.cpp)
add_executable(g5_bbox g5_bbox.cpp)
add_executable(g6_visit g6_visit.cpp)

