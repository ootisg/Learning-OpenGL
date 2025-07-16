cmake_minimum_required(VERSION 3.15)
project(project_lib VERSION 1.0)

find_package(OpenGL REQUIRED)

add_library(project_lib entry.c
    render.c
    scene.c
    camera.c
    buffers_gl.c
    shaders_gl.c
    textures_gl.c
    glad.c)

add_subdirectory(linalg)
add_subdirectory(inputs)

target_include_directories(project_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
    
target_link_libraries(project_lib PRIVATE
    linalg
    inputs)