#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
	FragColor = mix (texture (tex1, texCoord), texture (tex2, texCoord), 0.2);
}