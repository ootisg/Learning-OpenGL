#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

out vec2 texCoord;

uniform mat4 transform;

void main() {
   texCoord = texCoords;
   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}