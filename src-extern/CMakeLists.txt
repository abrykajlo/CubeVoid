include(FetchContent)

# GLAD
set(GLAD_PROFILE "core")
set(GLAD_ALL_EXTENSIONS ON)
FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

# GLFW
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
)

# GLM 
FetchContent_Declare(glm 
    GIT_REPOSITORY https://github.com/g-truc/glm.git
)
FetchContent_Populate(glm)

FetchContent_MakeAvailable(glm glfw glad)

# set include directories
set(GLAD_INCLUDE_DIRS ${GLAD_INCLUDE_DIRS} PARENT_SCOPE)
set(GLFW_INCLUDE_DIRS "${GLFW_SOURCE_DIR}/include" PARENT_SCOPE)
set(GLM_INCLUDE_DIRS "${glm_SOURCE_DIR}" PARENT_SCOPE)
