cmake_minimum_required(VERSION 3.8)

project(learn-vulkan)

find_package(PkgConfig)

pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(VK REQUIRED vulkan)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_VULKAN GLM_FORCE_RADIANS GLM_FORCE_DEPTH_ZERO_TO_ONE)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES} ${VK_LIBRARIES})

add_custom_target(run COMMAND ${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
