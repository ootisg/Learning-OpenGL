#version 330 core

out vec4 FragColor;

flat in vec3 normal;
in vec3 fragPos;

//uniform sampler2D tex1;
//uniform sampler2D tex2;

uniform vec3 lightPos;

vec3 lightColor = vec3 (1.0, 1.0, 1.0);
vec3 objColor = vec3 (1.0, 0.5, 0.31);
float ambient = 0.1;

void main() {
	vec3 ambientColor = lightColor * ambient;
	vec3 lightDir = normalize (lightPos - fragPos);
	float diffuseMag = max (dot (lightDir, normal), 0.0);
	vec3 diffuseColor = lightColor * diffuseMag;
	FragColor = vec4 ((ambientColor + diffuseColor) * objColor, 0.0);
}