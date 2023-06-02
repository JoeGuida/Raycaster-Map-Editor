cmake_minimum_required(VERSION 3.25)
project(Raycaster_Map_Editor)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

add_library(glfw STATIC IMPORTED include/transform.hpp)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION $ENV{GLFW_DIR}/build/lib/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES $ENV{GLFW_DIR}/include
)

include_directories($ENV{GLAD_DIR}/include $ENV{GLM_DIR} $ENV{IMGUI_DIR} include/)
file(GLOB imgui_sources $ENV{IMGUI_DIR}/**.cpp)

add_executable(Raycaster_Map_Editor src/main.cpp $ENV{GLAD_DIR}/src/glad.c ${imgui_sources} src/ray.cpp include/ray.hpp include/shader.hpp src/shader.cpp include/filesystem.hpp include/renderer.hpp src/renderer.cpp include/material.hpp include/transform.hpp)
target_link_libraries(Raycaster_Map_Editor OpenGL glfw X11)
