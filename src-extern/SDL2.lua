project "SDL2"
    kind "StaticLib"
    files { 
        "SDL/src/*.h",
        "SDL/src/*.c", 
    }
    includedirs { "SDL/include", "SDL/src" }