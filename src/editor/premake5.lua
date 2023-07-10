project "Editor"
    kind "WindowedApp"
    cppdialect "C++17"
    language "C++"

    files { "*.h", "*.cpp" }

    includedirs {
        "..",
        "../../src-extern/entt/src",
        "../../src-extern/glad/include",
        "../../src-extern/glm",
        "../../src-extern/imgui",
        "../../src-extern/SDL/include",
    }

    links { "glad", "SDL", "SDLmain", "imgui", "Core", "Engine", "Render" }

    debugdir "bin/Debug"

    postbuildcommands {
        "copy ..\\..\\Win32\\Debug\\SDL2.dll bin\\Debug\\SDL2.dll",
        "mkdir bin\\Debug\\assets",
        "mkdir bin\\Debug\\assets\\shaders",
        "copy ..\\render\\shaders\\fragment.glsl bin\\Debug\\assets\\shaders\\fragment.glsl",
        "copy ..\\render\\shaders\\vertex.glsl bin\\Debug\\assets\\shaders\\vertex.glsl",
    }