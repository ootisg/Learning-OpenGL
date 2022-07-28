#version 330 core

out vec4 FragColor;

flat in vec3 normal;
in vec3 fragPos;

//uniform sampler2D tex1;
//uniform sampler2D tex2;

uniform vec3 lightPos;
uniform vec3 eyePos;

vec3 lightColor = vec3 (1.0, 1.0, 1.0);
vec3 objColor = vec3 (1.0, 0.5, 0.31);
float ambient = 0.1;
float specularStrength = 0.5;
float highlightStrength = 32;

void main() {
	vec3 ambientColor = lightColor * ambient;
	vec3 lightDir = normalize (lightPos - fragPos);
	float diffuse = max (dot (lightDir, normal), 0.0);
	vec3 diffuseColor = lightColor * diffuse;
	vec3 viewDir = normalize (eyePos - fragPos);
	vec3 reflectDir = reflect (-lightDir, normal);
	float specular = pow (max (dot (viewDir, reflectDir), 0.0), highlightStrength);
	vec3 specularColor = lightColor * specular * specularStrength;
	FragColor = vec4 ((ambientColor + diffuseColor + specularColor) * objColor, 0.0);
}