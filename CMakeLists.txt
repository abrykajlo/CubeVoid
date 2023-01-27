cmake_minimum_required(VERSION 3.14)
project(CubeVoid)

find_package(OpenGL REQUIRED)

add_subdirectory(src-extern)
add_subdirectory(src/core)
add_subdirectory(src/render)
add_subdirectory(src/simulation)

add_subdirectory(src/games/cubevoid)