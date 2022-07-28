#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};

out vec4 FragColor;

flat in vec3 normal;
in vec3 fragPos;

//uniform sampler2D tex1;
//uniform sampler2D tex2;

uniform Light light;
uniform Material material;
uniform vec3 eyePos;

vec3 lightColor = vec3 (1.0, 1.0, 1.0);
vec3 objColor = vec3 (1.0, 0.5, 0.31);
float highlightStrength = 32;

void main() {

	vec3 ambientColor = light.ambient;
	
	vec3 lightDir = normalize (light.position - fragPos);
	float diffuse = max (dot (lightDir, normal), 0.0);
	vec3 diffuseColor = light.diffuse * diffuse;
	
	vec3 viewDir = normalize (eyePos - fragPos);
	vec3 reflectDir = reflect (-lightDir, normal);
	float specular = pow (max (dot (viewDir, reflectDir), 0.0), material.shininess);
	vec3 specularColor = light.specular * specular;
	
	FragColor = vec4 (ambientColor * material.ambient + diffuseColor * material.diffuse + specularColor * material.specular, 0.0);
	
}