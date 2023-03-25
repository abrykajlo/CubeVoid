add_library(Engine STATIC)

target_include_directories(Engine PRIVATE ${INCLUDE_DIRS})
target_sources(Engine PRIVATE clock.cpp clock.h game.cpp game.h)
target_compile_features(Engine PUBLIC cxx_std_17)
target_link_libraries(Engine
    PUBLIC
        Core
        Simulation
        Render
        glad::glad
        SDL2::SDL2main
)