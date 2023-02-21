add_library(Core)
target_include_directories(Core PRIVATE ..)
target_sources(Core
    PRIVATE
        log.cpp
        mat.cpp
        quat.cpp
        vec.cpp
)