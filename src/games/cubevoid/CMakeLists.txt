add_executable(CubeVoid main.cpp)

target_link_libraries(
    CubeVoid
    PRIVATE
        Engine
)
target_include_directories(CubeVoid PRIVATE ${INCLUDE_DIRS})
target_sources(CubeVoid PRIVATE cubevoid.cpp cubevoid.h)
target_compile_features(CubeVoid PUBLIC cxx_std_17)
set_property(TARGET CubeVoid PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:CubeVoid>)
configure_file(install/assets/models/dragon.obj assets/models/dragon.obj COPYONLY)
add_shaders()