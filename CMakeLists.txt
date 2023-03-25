cmake_minimum_required(VERSION 3.14)
project(CubeVoid)

add_subdirectory(src-extern)

set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/src
    ${ENTT_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
)

add_subdirectory(src/core)
add_subdirectory(src/render)
add_subdirectory(src/simulation)

add_subdirectory(src/engine)

add_subdirectory(src/games/cubevoid)
add_subdirectory(src/editor)

add_subdirectory(src/tests)