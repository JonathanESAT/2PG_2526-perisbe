--
-- premake5_config.lua
--
-- Premake solution to build the math framework.
-- Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
-- Math Library framework.
--
-- All rights are reserved.
--

PROJ_DIR = path.getabsolute("./..")

PROJECT_NAMES = {
  "PR00_UnitTest",
  "ML",
  "PR01_LibTest",
}


-- Solution workspace declaration:
workspace("ML_" .. _ACTION)
  location(PROJ_DIR .. "/build/")
  language "C++"
  cppdialect "C++20"
  startproject "PR00_UnitTest"
  platforms {
    "x32",
    "x64",
  }
  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }
  configurations { "Debug", "Release" }

-- Workspace "Debug" configuration:
filter { "configurations:Debug" }
  defines {
    "DEBUG",
  }
  symbols "On"
  warnings "Extra"
  targetsuffix "_d"

-- Workspace "Release" configuration:
filter { "configurations:Release" }
  defines {
    "NDEBUG",
  }
  symbols "Off"
  warnings "Extra"
  optimize "Size"
  flags {
    "No64BitChecks",
    "NoPCH",
  }


--[[*********************** UNITARY TEST PROJECT *************************]]--
function GenerateTestProject(project_name)
  project(project_name)
    kind "ConsoleApp"
    location (PROJ_DIR .. "/build/" .. project_name .. "/" .. _ACTION)
    includedirs {
      path.join(PROJ_DIR, "include/"),
    }
    files {
      -- ML:
      path.join(PROJ_DIR, "include/ML/*.h"),
      path.join(PROJ_DIR, "include/ML/*.inl"),
      path.join(PROJ_DIR, "tests/" .. project_name .. ".cc"),
    }
    removefiles {
      path.join(PROJ_DIR, "src/ML/**.cc"),
    }
    defines { "INLINED" }

    --Debug filters:
    filter { "configurations:Debug", "platforms:x32" }
      architecture "x86"
      targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
    filter { "configurations:Debug", "platforms:x64" }
      architecture "x86_64"
      targetdir (path.join(PROJ_DIR, "bin/Debug/x64"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
    --Release filters:
    filter { "configurations:Release", "platforms:x32" }
      architecture "x86"
      targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
    filter { "configurations:Release", "platforms:x64" }
      architecture "x86_64"
      targetdir (path.join(PROJ_DIR, "bin/Release/x64/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
    filter { }
end -- ************** UNITARY TEST PROJECT ends here.


--[[************************* STATIC LIB PROJECT *************************]]--
function GenerateLibProject(project_name)
  project(project_name)
    kind "StaticLib"
    location (PROJ_DIR .. "/build/" .. project_name .. "/" .. _ACTION)
    includedirs {
      path.join(PROJ_DIR, "include/"),
    }
    files {
      -- ML:
      path.join(PROJ_DIR, "include/ML/*.h"),
      path.join(PROJ_DIR, "include/ML/*.inl"),
      path.join(PROJ_DIR, "src/ML/*.cc"),
    }
    undefines { "INLINED" }

    --Debug filters:
    filter { "configurations:Debug", "platforms:x32" }
      architecture "x86"
      targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
    filter { "configurations:Debug", "platforms:x64" }
      architecture "x86_64"
      targetdir (path.join(PROJ_DIR, "bin/Debug/x64"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
    --Release filters:
    filter { "configurations:Release", "platforms:x32" }
      architecture "x86"
      targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
    filter { "configurations:Release", "platforms:x64" }
      architecture "x86_64"
      targetdir (path.join(PROJ_DIR, "bin/Release/x64/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
    filter { }
end -- ************** STATIC LIB PROJECT ends here.


--[[*********************** STATIC LIB TEST PROJECT **********************]]--
function GenerateLibTestProject(project_name, lib_dir_name)
  project(project_name)
    kind "ConsoleApp"
    location (PROJ_DIR .. "/build/" .. project_name .. "/" .. _ACTION)
    includedirs {
      path.join(PROJ_DIR, "include/"),
    }
    files {
      -- ML:
      path.join(PROJ_DIR, "include/ML/*.h"),
      path.join(PROJ_DIR, "tests/" .. project_name .. ".cc"),
    }
    removefiles {
      path.join(PROJ_DIR, "src/ML/**.cc"),
      path.join(PROJ_DIR, "include/ML/*.inl"),
    }
    undefines { "INLINED" }

    --Debug filters:
    filter { "configurations:Debug", "platforms:x32" }
      architecture "x86"
      libdirs { path.join(PROJ_DIR, "bin/Debug/x32"), }
      links { lib_dir_name .. "_d" }
      targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
    filter { "configurations:Debug", "platforms:x64" }
      architecture "x86_64"
      libdirs { path.join(PROJ_DIR, "bin/Debug/x64"), }
      links { lib_dir_name .. "_d" }
      targetdir (path.join(PROJ_DIR, "bin/Debug/x64"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
    --Release filters:
    filter { "configurations:Release", "platforms:x32" }
      architecture "x86"
      libdirs { path.join(PROJ_DIR, "bin/Release/x32"), }
      links { lib_dir_name }
      targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
    filter { "configurations:Release", "platforms:x64" }
      architecture "x86_64"
      libdirs { path.join(PROJ_DIR, "bin/Release/x64"), }
      links { lib_dir_name }
      targetdir (path.join(PROJ_DIR, "bin/Release/x64/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
    filter { }
end -- ************** STATIC LIB TEST PROJECT ends here.

GenerateTestProject(PROJECT_NAMES[1])
GenerateLibProject(PROJECT_NAMES[2])
GenerateLibTestProject(PROJECT_NAMES[3], PROJECT_NAMES[2])
