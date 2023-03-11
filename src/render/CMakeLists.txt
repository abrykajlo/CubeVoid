add_library(Render STATIC)
target_include_directories(Render PRIVATE .. ${GLM_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR})
target_sources(Render
    PUBLIC
        camera.cpp
        camera.h
        mesh.cpp
        mesh.h
        render.cpp
        render.h
        shader_program.cpp
        shader_program.h
        shader.cpp
        shader.h
)
target_link_libraries(Render 
    PRIVATE 
        glad::glad 
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)