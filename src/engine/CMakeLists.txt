add_library(Engine STATIC)

target_include_directories(Engine PRIVATE ..)
target_sources(Engine PRIVATE clock.cpp clock.h game.cpp game.h)
target_link_libraries(Engine PRIVATE Core Simulation Render glad::glad $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)