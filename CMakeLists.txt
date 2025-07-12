cmake_minimum_required(VERSION 3.15)
project(Learning_OpenGL VERSION 1.0)

find_package(OpenGL REQUIRED)

add_executable(Learning_OpenGL main.c
    render.c
    scene.c
    camera.c
    inputs.c
    buffers_gl.c
    shaders_gl.c
    textures_gl.c
    glad.c)

add_subdirectory(linalg)
    
target_link_libraries(Learning_OpenGL PRIVATE
    linalg)

target_link_directories(Learning_OpenGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(Learning_OpenGL PRIVATE
    ${OPENGL_LIBRARIES}
    "glfw3.lib"
    "zlibstaticd.lib"
    "assimp-vc143-mtd.lib")

target_include_directories(Learning_OpenGL PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)