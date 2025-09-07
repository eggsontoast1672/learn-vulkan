workspace "LearnVulkan"
  configurations { "Debug", "Release" }

project "VulkanCore"
  kind "StaticLib"
  language "C++"
  targetdir "bin/%{prj.name}/%{cfg.buildcfg}"

  files { "VulkanCore/**.hpp", "VulkanCore/**.cpp" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"

-- project "HelloWorld"
--   kind "ConsoleApp"
--   language "C"
--   targetdir "bin/%{cfg.buildcfg}"
-- 
--   files { "**.h", "**.c" }
-- 
--   filter "configurations:Debug"
--     defines { "DEBUG" }
--     symbols "On"
-- 
--   filter "configurations:Release"
--     defines { "NDEBUG" }
--     optimize "On"


