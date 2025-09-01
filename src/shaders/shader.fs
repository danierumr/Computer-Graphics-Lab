#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D diffuseTex;

void main() {
    FragColor = texture(diffuseTex, TexCoord) * vec4(lightColor * objectColor, 1.0);
}