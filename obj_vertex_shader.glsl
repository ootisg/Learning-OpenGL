#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 texCoords;

flat out vec3 correctedNormal;
out vec3 fragPos;
out vec2 texturePos;

uniform mat4 model;
uniform mat4 normal;
uniform mat4 view;
uniform mat4 proj;

void main() {
   correctedNormal = normalize (mat3 (normal) * vertexNormal);
   fragPos = vec3 (model * vec4 (aPos, 0.0));
   texturePos = texCoords;
   gl_Position = proj * view * model * vec4(aPos, 1.0);
}