#version 430 core

// Vertex Data Interpretation
layout(location = 0) in vec3 position;

// Inputs via Uniforms
uniform mat4 matView;
uniform mat4 matProjection;

// Outputs to Fragment Shader
out vec3 fragTexCoords;

// Shader Functionality
void main() {
	// Ensure the Translation was removed from the View Matrix so the Skybox does NOT move
	mat4 matViewNoTranslation = mat4(mat3(matView));

	// Keeps the Skybox behind Everything (z = w)
	gl_Position = (matProjection * matViewNoTranslation * vec4(position, 1.0f)).xyww;
	fragTexCoords = vec3(position.xyz);
}