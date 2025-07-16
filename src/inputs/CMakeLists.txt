project(inputs VERSION 1.0)

add_library(inputs STATIC
    inputs.c)

target_include_directories(inputs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})