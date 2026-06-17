#version 430 core

// Inputs via Uniforms
uniform vec3 objectColor;

// Outputs
out vec4 finalColor;

// Shader Functionality
void main() {
	finalColor = vec4(objectColor, 1.0f);
}