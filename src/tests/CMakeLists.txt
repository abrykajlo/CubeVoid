add_executable(tests ../core/tests.cpp)
target_include_directories(tests PRIVATE ..)
target_link_libraries(tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain Core)