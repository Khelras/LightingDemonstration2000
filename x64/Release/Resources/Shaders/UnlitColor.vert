#version 430 core

// Vertex Data Interpretation
layout(location = 0) in vec3 position;

// Inputs via Uniforms
uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

// Shader Functionality
void main() {
	gl_Position = matProjection * matView * matModel * vec4(position, 1.0f);
}