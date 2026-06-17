#version 430 core

// Vertex Data Interpretation
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 instanceMatrixCol1;
layout(location = 4) in vec4 instanceMatrixCol2;
layout(location = 5) in vec4 instanceMatrixCol3;
layout(location = 6) in vec4 instanceMatrixCol4;

// Inputs via Uniforms
//uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

// Outputs to Fragment Shader
out vec2 fragTexCoords;
out vec3 fragNormal;
out vec3 fragWorldPosition;

// Shader Functionality
void main() {
	// Construct the Model Matrix from all Instance Vec4s
	mat4 instanceModel = mat4(
		instanceMatrixCol1,
		instanceMatrixCol2,
		instanceMatrixCol3,
		instanceMatrixCol4
	);

	gl_Position = matProjection * matView * instanceModel * vec4(position, 1.0f);

	fragTexCoords = texCoords;
	fragNormal = mat3(transpose(inverse(instanceModel))) * normal;
	fragWorldPosition = vec3(instanceModel * vec4(position, 1.0f));
}