project "imgui"
    kind "StaticLib"

    files {
        "imgui/imgui.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/backends/imgui_impl_opengl3.cpp",
        "imgui/backends/imgui_impl_sdl2.cpp",
    }

    includedirs { "imgui", "SDL/include" }