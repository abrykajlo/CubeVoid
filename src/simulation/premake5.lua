project "Simulation"
    kind "StaticLib"
    cppdialect "C++17"

    files { "**.h", "**.cpp" }

    includedirs {
        "..",
        "../../src-extern/entt/src",
    }