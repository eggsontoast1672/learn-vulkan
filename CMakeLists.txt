cmake_minimum_required(VERSION 3.12)

project(LearnVulkan LANGUAGES CXX)

find_package(PkgConfig)

pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(VULKAN REQUIRED vulkan)

add_executable(learnvulkan src/main.cpp)

set_property(TARGET learnvulkan PROPERTY CXX_STANDARD 20)
set_property(TARGET learnvulkan PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET learnvulkan PROPERTY CXX_EXTENSIONS OFF)

target_compile_definitions(learnvulkan PRIVATE GLFW_INCLUDE_VULKAN)
target_link_libraries(learnvulkan PRIVATE ${GLFW_LIBRARIES} ${VULKAN_LIBRARIES})
