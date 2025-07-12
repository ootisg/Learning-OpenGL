#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float innerCutoff;
	float outerCutoff;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

flat in vec3 correctedNormal;
in vec3 fragPos;
in vec2 texturePos;

uniform sampler2D tex2;

uniform DirLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotlight;

uniform Material material;
uniform vec3 eyePos;

vec3 lightColor = vec3 (1.0, 1.0, 1.0);
vec3 objColor = vec3 (1.0, 0.5, 0.31);
float highlightStrength = 32;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize (-light.direction);
	vec3 ambient = light.ambient * vec3 (texture (material.diffuse, texturePos));
	vec3 diffuse = light.diffuse * max (dot (lightDir, normal), 0.0) * vec3 (texture (material.diffuse, texturePos));
	vec3 reflectDir = reflect (-lightDir, normal);
	vec3 specular = light.specular * pow (max (dot (viewDir, reflectDir), 0.0), material.shininess) * vec3 (texture (material.specular, texturePos));
	return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize (light.position - fragPos);
	vec3 ambient = light.ambient * vec3 (texture (material.diffuse, texturePos));
	vec3 diffuse = light.diffuse * max (dot (lightDir, normal), 0.0) * vec3 (texture (material.diffuse, texturePos));
	vec3 reflectDir = reflect (-lightDir, normal);
	vec3 specular = light.specular * pow (max (dot (viewDir, reflectDir), 0.0), material.shininess) * vec3 (texture (material.specular, texturePos));
	float dist = length (light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
	return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize (-light.direction);
	float theta = dot (-lightDir, viewDir);
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = clamp ((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
	if (theta > light.outerCutoff) {
		vec3 diffuse = light.diffuse * max (dot (-lightDir, normal), 0.0) * vec3 (texture (material.diffuse, texturePos));
		vec3 reflectDir = reflect (-lightDir, normal);
		vec3 specular = light.specular * pow (max (dot (viewDir, reflectDir), 0.0), material.shininess) * vec3 (texture (material.specular, texturePos));
		return (diffuse + specular) * intensity;
	} else {
		return vec3 (0);
	}
}

void main() {
	
	vec3 viewDir = normalize (eyePos - fragPos);
	vec3 lighting = vec3 (0.0);
	lighting += calcDirLight (dirLight, correctedNormal, viewDir);
	lighting += calcPointLight (pointLights[0], correctedNormal, fragPos, viewDir);
	lighting += calcPointLight (pointLights[1], correctedNormal, fragPos, viewDir);
	lighting += calcPointLight (pointLights[2], correctedNormal, fragPos, viewDir);
	lighting += calcPointLight (pointLights[3], correctedNormal, fragPos, viewDir);
	lighting += calcSpotLight (spotlight, correctedNormal, fragPos, viewDir);
	FragColor = vec4 (lighting, 1.0);
	
}