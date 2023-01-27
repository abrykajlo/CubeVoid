add_library(Simulation STATIC simulation.cpp)
target_include_directories(Simulation PUBLIC .. ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS})