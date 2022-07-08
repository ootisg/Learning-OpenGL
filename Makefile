main: main.c inputs buffers_gl shaders_gl textures_gl vector matrix render
	gcc -g main.c inputs.o buffers_gl.o shaders_gl.o textures_gl.o render.o vector.o matrix.o -lglfw3 -lopengl32 -lgdi32 -lglew32 -Iinclude
inputs: inputs.c inputs.h
	gcc -c -g inputs.c -Iinclude
buffers_gl: buffers_gl.c buffers_gl.h
	gcc -c -g buffers_gl.c -Iinclude
shaders_gl: shaders_gl.c shaders_gl.h
	gcc -c -g shaders_gl.c -Iinclude
textures_gl: textures_gl.c textures_gl.h
	gcc -c -g textures_gl.c -Iinclude
vector: vector.c vector.h
	gcc -c -g vector.c
matrix: matrix.c matrix.h
	gcc -c -g matrix.c
render: render.c render.h
	gcc -c -g render.c -Iinclude