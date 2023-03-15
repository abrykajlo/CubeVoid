add_library(Simulation STATIC)
target_include_directories(Simulation PRIVATE ${INCLUDE_DIRS})
target_sources(Simulation
    PUBLIC
        components.h
        simulation.cpp 
        simulation.h
)
target_compile_features(Simulation PUBLIC cxx_std_17)