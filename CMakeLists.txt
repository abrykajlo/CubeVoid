cmake_minimum_required(VERSION 3.14)
project(CubeVoid)

add_subdirectory(extern-src)
add_subdirectory(src/core)
add_subdirectory(src/render)
add_subdirectory(src/simulation)

add_subdirectory(src/games/cubevoid)

add_subdirectory(src/tests)