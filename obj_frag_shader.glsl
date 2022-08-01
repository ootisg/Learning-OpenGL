#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	float constant;
	float linear;
	float quadratic;
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
	
	//Calculate attenuation
	float dist = length (light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
	
	//Output as final vec4
	FragColor = vec4 (light.ambient * vec3 (texture (material.diffuse, texturePos)) * attenuation + diffuseColor * vec3 (texture (material.diffuse, texturePos)) * attenuation + specularColor * vec3 (texture (material.specular, texturePos)) * attenuation, 0.0);
	
}