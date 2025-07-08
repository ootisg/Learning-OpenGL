cmake_minimum_required(VERSION 3.15)
project(Learning_OpenGL VERSION 1.0)

find_package(OpenGL REQUIRED)

add_executable(Learning_OpenGL main.c
                        render.c
                        scene.c
                        camera.c
                        buffers_gl.c
                        shaders_gl.c
                        textures_gl.c
                        inputs.c
                        matrix.c
                        vector.c
                        glad.c)
target_link_directories(Learning_OpenGL PUBLIC
                        "./lib")
target_link_libraries(Learning_OpenGL
                      ${OPENGL_LIBRARIES}
                      "glfw3.lib"
		      "zlibstaticd.lib"
                      "assimp-vc143-mtd.lib")

include_directories(${OPENGL_INCLUDE_DIR}
                    "./include")