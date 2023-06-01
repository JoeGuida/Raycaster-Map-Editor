cmake_minimum_required(VERSION 3.25)
project(Raycaster_Map_Editor)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION $ENV{GLFW_DIR}/build/lib/libglfw3.a
        INTERFACE_INCLUDE_DIRECTORIES $ENV{GLFW_DIR}/include
        )

include_directories($ENV{GLAD_DIR}/include $ENV{GLM_DIR} $ENV{IMGUI_DIR})
file(GLOB imgui_sources $ENV{IMGUI_DIR}/**.cpp)

add_executable(Raycaster_Map_Editor src/main.cpp $ENV{GLAD_DIR}/src/glad.c ${imgui_sources})
target_link_libraries(Raycaster_Map_Editor OpenGL glfw X11)
