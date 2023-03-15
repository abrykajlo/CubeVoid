add_library(Core)
target_include_directories(Core PRIVATE ${INCLUDE_DIRS})
target_sources(Core
    PUBLIC
        log.cpp
        log.h
        math.h
)