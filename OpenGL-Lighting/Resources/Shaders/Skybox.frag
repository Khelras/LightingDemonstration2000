#version 430 core

// Inputs from Vertex Shader
in vec3 fragTexCoords;

// Inputs via Unifroms
uniform samplerCube textureSkybox;

// Outputz
out vec4 finalColor;

void main() {
    finalColor = texture(textureSkybox, fragTexCoords);
}