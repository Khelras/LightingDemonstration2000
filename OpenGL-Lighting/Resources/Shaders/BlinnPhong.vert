#version 430 core

// Vertex Data Interpretation
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

// Inputs via Uniforms
uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

// Outputs to Fragment Shader
out vec2 fragTexCoords;
out vec3 fragNormal;
out vec3 fragWorldPosition;

// Shader Functionality
void main() {
	gl_Position = matProjection * matView * matModel * vec4(position, 1.0f);
	fragTexCoords = texCoords;

	fragTexCoords = texCoords;
	fragNormal = mat3(transpose(inverse(matModel))) * normal;
	fragWorldPosition = vec3(matModel * vec4(position, 1.0f));
}