project "glad"
    kind "StaticLib"

    files { "glad/**.h", "glad/**.c" }

    includedirs { "glad/include" }