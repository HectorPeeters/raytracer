workspace "Raytracer"
    configurations { "Debug", "Release" }
    startproject "OpenGLBoilerPlate"

    flags { "MultiProcessorCompile", "FatalWarnings" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "Raytracer"
    kind "StaticLib"
    language "C++"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { "include/" }
    
    files { "src/*.cpp" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

project "Editor"
    kind "ConsoleApp"
    language "C++"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { "editor/include/", "libs/glad/include/", "libs/glfw/include/", "libs/imgui/", "libs/imgui/examples", "libs/parson", "include/" }
    
    files { "editor/src/*.cpp", "editor/src/panels/*.cpp" }

    links { "GLFW", "GLAD", "ImGui", "Parson", "Raytracer" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

project "Tests"
    kind "ConsoleApp"
    language "C++"
    architecture "x86_64"
    
    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"
    
    includedirs { "include/", "libs/catch2/" }
        
    files { "tests/*.cpp" }
    
    links { "Raytracer", "Catch2" }
    
    filter "system:linux"
        links { "dl", "pthread" }
    
        defines { "_X11" }
    
    filter "system:windows"
        defines { "_WINDOWS" }

include "libs/glfw.lua"
include "libs/glad.lua"
include "libs/imgui.lua"
include "libs/parson.lua"
include "libs/catch2.lua"
