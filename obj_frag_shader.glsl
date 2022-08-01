#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};

out vec4 FragColor;

flat in vec3 correctedNormal;
in vec3 fragPos;
in vec2 texturePos;

uniform sampler2D tex2;

uniform Light light;
uniform Material material;
uniform vec3 eyePos;

vec3 lightColor = vec3 (1.0, 1.0, 1.0);
vec3 objColor = vec3 (1.0, 0.5, 0.31);
float highlightStrength = 32;

void main() {
	
	vec3 lightDir = normalize (light.position - fragPos);
	
	//Calculate diffuse component
	float diffuse = max (dot (lightDir, correctedNormal), 0.0);
	vec3 diffuseColor = light.diffuse * diffuse;
	
	//Calculate specular component
	vec3 viewDir = normalize (eyePos - fragPos);
	vec3 reflectDir = reflect (-lightDir, correctedNormal);
	float specular = pow (max (dot (viewDir, reflectDir), 0.0), material.shininess);
	vec3 specularColor = light.specular * specular;
	
	//Spotlight calculation
	float theta = dot (light.direction, lightDir);
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp ((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
	if (theta > light.outerCutoff) {
		FragColor = vec4 (light.ambient * vec3 (texture (material.diffuse, texturePos)) + diffuseColor * vec3 (texture (material.diffuse, texturePos)) * intensity + specularColor * vec3 (texture (material.specular, texturePos)) * intensity, 0.0);
	} else {
		FragColor = vec4 (light.ambient * vec3 (texture (material.diffuse, texturePos)), 0.0);
	}
	
}