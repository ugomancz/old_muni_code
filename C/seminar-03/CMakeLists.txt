cmake_minimum_required(VERSION 3.5)
project(cviceni03)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -Wall -Wextra -pedantic")

set(CALC_SOURCE_FILES main.c)
add_executable(calc ${CALC_SOURCE_FILES})
target_compile_definitions(calc PRIVATE __USE_MINGW_ANSI_STDIO=1)
