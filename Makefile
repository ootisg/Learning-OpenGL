main: main.c inputs buffers_gl shaders_gl textures_gl vector matrix render camera material scene model mesh
	gcc -g main.c inputs.o buffers_gl.o shaders_gl.o textures_gl.o render.o camera.o vector.o matrix.o scene.o model.o mesh.o lib/assimp-vc142-mt.dll -lglfw3 -lopengl32 -lgdi32 -lglew32 -Iinclude
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
render: render.c render.h render_info.h
	gcc -c -g render.c -Iinclude
camera: camera.c camera.h
	gcc -c -g camera.c -Iinclude
material: material.c material.h
	gcc -c -g material.c -Iinclude
mesh: mesh.c mesh.h
	gcc -c -g mesh.c -Iinclude
model: model.c model.h
	gcc -c -g model.c -Iinclude
scene: scene.c scene.h
	gcc -c -g scene.c -Iinclude