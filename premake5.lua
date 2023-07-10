workspace "CubeVoid"
    configurations { "Debug", "Release" }
    startproject "CubeVoid"

group "Games"
    include "src/games/cubevoid"

group "Engine"
    include "src/core"
    include "src/render"
    include "src/simulation"
    include "src/engine"

group "Tests"

group "Tools"
    include "src/editor"

group "Extern"
    include "src-extern"