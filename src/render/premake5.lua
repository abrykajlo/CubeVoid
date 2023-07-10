project "Render"
    kind "StaticLib"
    cppdialect "C++17"

    files { "**.h", "**.cpp" }

    includedirs {
        "..",
        "../../src-extern/entt/src",
        "../../src-extern/glad/include",
        "../../src-extern/glm",
        "../../src-extern/SDL/include",
    }

renderLinks = { "glad", "SDL2", "Render" }
