add_library(Core)
target_include_directories(Core PRIVATE ..)
target_sources(Core
    PUBLIC
        log.cpp
        log.h
        math.h
        util.h
)