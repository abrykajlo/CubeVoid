add_library(Render STATIC)
target_include_directories(Render PRIVATE ${INCLUDE_DIRS})
target_sources(Render
    PUBLIC
        camera.cpp
        camera.h
        components.h
        mesh.cpp
        mesh.h
        render.cpp
        render.h
        shader_program.cpp
        shader_program.h
        shader.cpp
        shader.h
)
target_compile_features(Render PUBLIC cxx_std_17)
target_link_libraries(Render PRIVATE $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)