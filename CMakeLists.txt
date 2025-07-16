cmake_minimum_required(VERSION 3.15)
project(Learning_OpenGL VERSION 1.0)

find_package(OpenGL REQUIRED)

add_executable(Learning_OpenGL main.c)

include_directories(${OPENGL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

target_link_directories(Learning_OpenGL PUBLIC
    ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(Learning_OpenGL PUBLIC
    ${OPENGL_LIBRARIES}
    "glfw3.lib"
    "zlibstatic.lib"
    "assimp-vc143-mt.lib")

target_link_libraries(Learning_OpenGL PRIVATE
    project_lib)