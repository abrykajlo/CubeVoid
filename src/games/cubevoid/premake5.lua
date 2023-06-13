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

    links { "SDL2" }