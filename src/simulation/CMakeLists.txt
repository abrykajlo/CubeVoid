add_library(Simulation STATIC)
target_include_directories(Simulation PRIVATE ..)
target_sources(Simulation PUBLIC simulation.cpp simulation.h)
target_link_libraries(Simulation PRIVATE glad::glad)
