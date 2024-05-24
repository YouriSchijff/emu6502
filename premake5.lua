workspace "6502 Emulator"
    warnings "Off"

    architecture "x64"

    configurations { "Debug" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "6502"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files { "src/**.h", "src/**.cpp" }

    includedirs { "src" }

    targetdir("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir("../bin/obj/" .. OutputDir .. "/%{prj.name}")

    filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"