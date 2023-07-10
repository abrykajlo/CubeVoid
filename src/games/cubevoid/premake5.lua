project "CubeVoid"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"

    files {
        "**.h",
        "**.cpp",
        "../../**.h",
        "../../../src-extern/entt/src/**.hpp",
    }

    includedirs {
        "../..",
        "../../../src-extern/entt/src",
        "../../../src-extern/glad/include",
        "../../../src-extern/glm",
        "../../../src-extern/SDL/include",
    }

    links { "glad", "SDL", "SDLmain", "Core", "Engine", "Simulation", "Render" }

    debugdir "bin/Debug"

    postbuildcommands {
        "copy ..\\..\\..\\Win32\\Debug\\SDL2.dll bin\\Debug\\SDL2.dll",
        "mkdir bin\\Debug\\assets",
        "mkdir bin\\Debug\\assets\\shaders",
        "copy ..\\..\\render\\shaders\\fragment.glsl bin\\Debug\\assets\\shaders\\fragment.glsl",
        "copy ..\\..\\render\\shaders\\vertex.glsl bin\\Debug\\assets\\shaders\\vertex.glsl",
    }