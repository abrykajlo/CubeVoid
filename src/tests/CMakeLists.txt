add_executable(Tests ../core/tests.cpp)
target_include_directories(Tests PRIVATE ${INCLUDE_DIRS})
target_link_libraries(Tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain Core)