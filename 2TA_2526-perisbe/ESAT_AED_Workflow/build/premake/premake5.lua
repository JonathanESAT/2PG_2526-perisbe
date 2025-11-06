-- premake5.lua 
workspace "ESAT_AED_Workflow"
  language "C++"
  configurations { "Debug", "Release" }
  platforms { "x86", "x64" }
  location "."                -- genera la .sln en esta carpeta
  startproject "App"
  flags { "MultiProcessorCompile" }

  -- Arquitectura por plataforma
  filter "platforms:x86"
    architecture "x86"
  filter "platforms:x64"
    architecture "x86_64"
  filter {}

  -- Ajustes por configuracion
  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
    targetsuffix "-d"
  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "Speed"
  filter {}

-- ========= PROYECTO LIBRERIA =========
project "MathLib"
  kind "StaticLib"
  targetdir ("../../bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")
  objdir    ("../../obj/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")
  includedirs { "../../MathLib/include" }
  files {
    "../../MathLib/include/**.h",
    "../../MathLib/src/**.cpp"
  }

-- ========= PROYECTO APLICACION =========
project "App"
  kind "ConsoleApp"
  targetdir ("../../bin/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")
  objdir    ("../../obj/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")
  includedirs { "../../App/include", "../../MathLib/include" }
  links { "MathLib" }
  files {
    "../../App/include/**.h",
--  "../../App/src/**.cpp",
    "../../App/src/**.c" 
  }
