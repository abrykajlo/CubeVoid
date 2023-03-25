include(FetchContent)

# Catch2
find_package(Catch2 CONFIG REQUIRED GLOBAL)

# ENTT
find_path(ENTT_INCLUDE_DIR entt/entt.hpp REQUIRED)
set(ENTT_INCLUDE_DIR ${ENTT_INCLUDE_DIR} PARENT_SCOPE)

# GLAD
set(GLAD_PROFILE "core")
set(GLAD_ALL_EXTENSIONS ON)
find_package(glad CONFIG REQUIRED GLOBAL)

# GLM 
find_path(GLM_INCLUDE_DIR glm/glm.hpp REQUIRED)
set(GLM_INCLUDE_DIR ${GLM_INCLUDE_DIR} PARENT_SCOPE)

# SDL2
find_package(SDL2 CONFIG REQUIRED GLOBAL)
find_path(SDL2_SOURCE_DIR SDL2/SDL.h REQUIRED)

# IMGUI
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG origin/docking
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(imgui)
add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR} ${SDL2_SOURCE_DIR}/SDL2)
target_sources(imgui
    INTERFACE
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

