#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexNormal;

flat out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
   normal = vertexNormal;
   fragPos = aPos;
   gl_Position = proj * view * model * vec4(aPos, 1.0);
}