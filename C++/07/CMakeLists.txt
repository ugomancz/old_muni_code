cmake_minimum_required(VERSION 3.19)
project(07)

set(CMAKE_CXX_STANDARD 17)

add_executable(g1_unrolled g1_unrolled.cpp)
add_executable(g2_bittrie g2_bittrie.cpp)
add_executable(g3_solid g3_solid.cpp)
add_executable(g4_chartrie g4_chartrie.cpp)
add_executable(g5_bdd g5_bdd.cpp)
add_executable(g6_rope g6_rope.cpp)