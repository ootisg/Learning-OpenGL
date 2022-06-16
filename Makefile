main: main.c inputs
	gcc main.c -lglfw3 -lopengl32 -lgdi32 -lglew32 -Iinclude inputs.o
inputs: inputs.c inputs.h
	gcc -c inputs.c -Iinclude