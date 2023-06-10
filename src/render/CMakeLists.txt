add_library(Render STATIC)
target_include_directories(Render PRIVATE ${INCLUDE_DIRS})
target_sources(Render
    PUBLIC
        camera.cpp
        camera.h
        components.h
        context.cpp
        context.h
        frame_buffer.cpp
        frame_buffer.h
        mesh.cpp
        mesh.h
        render.cpp
        render.h
        shader_program.cpp
        shader_program.h
        shader.cpp
        shader.h
        texture.cpp
        texture.h
        window.cpp
        window.h
)
target_compile_features(Render PUBLIC cxx_std_17)
target_link_libraries(Render PUBLIC $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)

set(SHADER_OUTPUT_DIR assets/shaders PARENT_SCOPE)
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders PARENT_SCOPE)
macro(add_shaders)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/${SHADER_OUTPUT_DIR})
set(VERTEX_OUTPUT ${OUTPUT_DIR}/)
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/${SHADER_OUTPUT_DIR} 
    COMMAND "${CMAKE_COMMAND} -E copy ")
endmacro()
