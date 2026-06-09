#version 430 core

// Inputs from Vertex Shader
in vec2 fragTexCoords;
in vec3 fragNormal;
in vec3 fragWorldPosition;

// Inputes via Unifroms
uniform sampler2D texture0;
uniform sampler2D reflectionMap;
uniform samplerCube skyboxTexture;
uniform vec3 cameraPosition;

// Outputs
out vec4 finalColor;

void main() {
	// View Direction FROM the Camera TOWARD the fragment (Incident Vector)
	vec3 viewDirection = normalize(fragWorldPosition - cameraPosition);

	// Normalize the Surface Normal
	vec3 norm = normalize(fragNormal);

	// Reflect the Incident Vector's View Direction around the Surface Normal
	vec3 reflectDirection = reflect(viewDirection, norm);

	// Sample the Object's own Texture
	vec4 objectColor = texture(texture0, fragTexCoords);

	// Sample the Skybox Cube Map
	vec4 reflectionColor = texture(skyboxTexture, reflectDirection);

	// Sample the Reflection Map
	float reflectionAmount = texture(reflectionMap, fragTexCoords).r;

	// Mix the Object Color and the Reflection Color based on the Reflection Amount
	finalColor = mix(objectColor, reflectionColor, reflectionAmount);
}