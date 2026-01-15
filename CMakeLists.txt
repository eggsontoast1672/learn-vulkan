cmake_minimum_required(VERSION 3.10)

project(LittleVulkanEngine LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(glfw3 CONFIG REQUIRED)

add_executable(
  lve
  include/lve/first_app.h
  include/lve/window.h
  src/first_app.c
  src/main.c
  src/window.c
)

set_property(TARGET lve PROPERTY C_STANDARD 11)
set_property(TARGET lve PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET lve PROPERTY C_EXTENSIONS OFF)

target_include_directories(lve PRIVATE include)
target_link_libraries(lve PRIVATE glfw)
