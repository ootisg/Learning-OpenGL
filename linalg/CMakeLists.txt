project(linalg VERSION 1.0)

add_library(linalg STATIC
    matrix.c
    vector.c)

target_include_directories(linalg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(linalg PRIVATE
    ${CMAKE_SOURCE_DIR}/include)