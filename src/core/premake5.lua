project "Core"
    kind "StaticLib"
    cppdialect "C++17"

    files { "**.h", "**.cpp" }

    removefiles { "tests.cpp" }

    includedirs { ".." }