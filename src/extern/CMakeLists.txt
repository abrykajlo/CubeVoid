include(FetchContent)

# GLAD
set(GLAD_PROFILE "core")
set(GLAD_ALL_EXTENSIONS ON)
FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)
set(GLAD_INCLUDE_DIRS ${GLAD_INCLUDE_DIRS} PARENT_SCOPE)

# GLFW
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_MakeAvailable(glfw)
set(GLFW_INCLUDE_DIRS "${GLFW_SOURCE_DIR}/include" PARENT_SCOPE)

# assimp
FetchContent_Declare(assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
)
FetchContent_MakeAvailable(assimp)
