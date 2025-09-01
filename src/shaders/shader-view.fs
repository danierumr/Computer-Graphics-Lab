#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

uniform vec3 baseColor;

uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D diffuseTex;
uniform bool useTexture;

void main() {

    float ambientStrnght = 0.1;
    vec3 ambient = ambientStrnght * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    // TO-DO
    // 32 is the shininess of the object (might want to change that later to be a propertie of object)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 resultColor = (ambient + diffuse + specular) * baseColor;


    if (useTexture) {
        FragColor = texture(diffuseTex, TexCoord) * vec4(resultColor, 1.0);
    } else {
        FragColor = vec4(resultColor, 1.0);
    }
}