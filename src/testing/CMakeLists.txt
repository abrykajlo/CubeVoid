add_executable(testing ../render/testing.cpp)
target_link_libraries(testing PRIVATE Catch2::Catch2WithMain)