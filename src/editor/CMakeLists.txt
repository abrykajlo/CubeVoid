add_executable(Editor main.cpp)
target_include_directories(Editor PRIVATE ${INCLUDE_DIRS})
target_sources(Editor PRIVATE editor.cpp editor.h)
target_link_libraries(Editor PRIVATE Engine imgui)

add_shaders()
