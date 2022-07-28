#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform vec3 lightPos;

vec3 objColor = vec3 (1.0, 0.5, 0.31);
float ambient = 0.1;

void main() {
	FragColor = vec4 (ambient * objColor, 0.0);
}