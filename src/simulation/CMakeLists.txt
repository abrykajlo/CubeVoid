add_library(Simulation STATIC simulation.cpp)
target_include_directories(Simulation PRIVATE ..)
target_link_libraries(Simulation PRIVATE glad::glad)
