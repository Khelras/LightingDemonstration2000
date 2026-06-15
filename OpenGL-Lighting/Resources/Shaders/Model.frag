#version 430 core

// Inputs from Vertex Shader
in vec2 fragTexCoords;
in vec3 fragNormal;
in vec3 fragWorldPosition;

// Inputes via Unifroms
uniform sampler2D texture0;
uniform vec3 cameraPosition;

// Outputs
out vec4 finalColor;

void main() {
	finalColor = texture(texture0, fragTexCoords);
}