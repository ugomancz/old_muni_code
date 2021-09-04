cmake_minimum_required(VERSION 3.10)
project(hw05 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Wextra -Werror -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L")
set(CMAKE_C_STANDARD 99)

add_executable(find5 find5.c)