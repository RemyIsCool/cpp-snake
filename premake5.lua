---@diagnostic disable: undefined-global
workspace "Snake"
configurations { "Debug", "Release" }
architecture "x86_64"

project "Snake"
kind "ConsoleApp"
language "C++"
cppdialect "C++latest"
targetdir "bin/%{cfg.buildcfg}"

files { "src/**.cpp", "src/**.h" }

includedirs { "include" }
libdirs { "lib" }
links { "raylib" }

filter "system:macosx"
links { "pthread", "dl", "objc" }
linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework IOKit", "-framework CoreVideo" }

filter "system:windows"
links { "winmm", "gdi32", "opengl32" }

filter "system:linux"
links { "pthread", "GL", "m" }

filter "configurations:Debug"
symbols "On"

filter "configurations:Release"
optimize "On"
