#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};
  

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 baseColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D diffuseTex;
uniform bool useTexture;

uniform Material material;
uniform Light lightIntensities;

void main() {

    // ambient
    vec3 ambient = lightIntensities.ambientIntensity * lightColor * material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightIntensities.diffuseIntensity * lightColor * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightIntensities.specularIntensity * lightColor * (spec * material.specular);

    vec3 resultColor = (ambient + diffuse + specular) * baseColor;

    if (useTexture) {
        FragColor = texture(diffuseTex, TexCoord) * vec4(resultColor, 1.0);
    } else {
        FragColor = vec4(resultColor, 1.0);
    }
}