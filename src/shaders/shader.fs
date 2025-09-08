#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
    vec3 baseColor;
    bool emissive;
};

struct Light {
    vec3 position;
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {

    // ambient
    // vec3 ambient = light.ambientIntensity * light.color * material.baseColor;
    vec3 ambient = light.ambientIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuseIntensity * light.color * diff * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specularIntensity * light.color * spec * texture(material.specular, TexCoord).rgb;

    // emission
    vec3 emission = vec3(0.0);
    if (material.emissive) {
        // if there is no specular, so it stays inside the box
        if (texture(material.specular, TexCoord).rgb == vec3(0.0)) {
            emission = texture(material.emission, TexCoord).rgb;
        }
    }

    vec3 result = (ambient + diffuse + specular + emission);
    FragColor = vec4(result, 1.0);

}