add_library(Render STATIC)
target_include_directories(Render PRIVATE ..)
target_sources(Render
    PUBLIC
        camera.cpp
        mesh.cpp
        render.cpp
        shader_program.cpp
        shader.cpp
)
target_link_libraries(Render PRIVATE glad::glad)