-- premake5.lua
workspace "OMT Studio"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "OMT Studio"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Build-Walnut-External.lua"
include "OMT Studio/Build-OMT-Studio.lua"
