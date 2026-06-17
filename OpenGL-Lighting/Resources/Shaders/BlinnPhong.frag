#version 430 core

// -- Light Structs -- //
struct PointLight {
    // Light Properties
    vec3 position;
    vec3 color;
    float specularStrength;

    // Attenuation
    float attenuationConstant;
    float attenuationLinear;
    float attenuationExponent;
};

struct DirectionalLight {
    // Light Properties
    vec3 direction;
    vec3 color;
    float specularStrength;
};

struct SpotLight {
    // Light Properties
    vec3 position;
    vec3 direction;
    vec3 color;
    float specularStrength;

    // Cone Angles
    float innerCutoffAngle;
    float outerCutoffAngle;
};
// -- //



// -- Uniforms -- //
#define MAX_POINT_LIGHTS 4

// Globals
uniform sampler2D imageTexture;
uniform vec3 cameraPosition;
uniform float shininess;

// Ambient
uniform vec3 ambientColor;
uniform float ambientStrength;

// Point Lights
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;
uniform bool pointLightsEnabled;

// Directional
uniform DirectionalLight dirLight;
uniform bool dirLightEnabled;

// Spot
uniform SpotLight spotLight;
uniform bool spotLightEnabled;
// -- //



// -- Inputs and Outputs -- //
// Inputs from Vertex Shader
in vec2 fragTexCoords;
in vec3 fragNormal;
in vec3 fragWorldPosition;

// Outputs
out vec4 finalColor;
// -- //



// -- Functions -- // 
// Point Light Calculation
vec3 calculatePointLight(int index, vec3 norm, vec3 fragPos, vec3 reverseViewDir)
{
    // Point Light to Calculate
    PointLight light = pointLights[index];

    // Direction from the Fragment to the Point Light Source
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * light.color;

    // Specular
    vec3 halfwayDir = normalize(lightDir + reverseViewDir);
    float specReflectivity = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = light.specularStrength * specReflectivity * light.color;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (
        light.attenuationConstant + light.attenuationLinear * distance + light.attenuationExponent  * (distance * distance));

    // Apply Attenuation to both Diffuse and Specular
    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}

// Directional Light Calculation
vec3 calculateDirectionalLight(vec3 norm, vec3 reverseViewDir)
{
    // Direction from the Surface to the Light
    vec3 lightDir = normalize(-dirLight.direction);

    // Diffuse
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * dirLight.color;

    // Specular
    vec3 halfwayDir = normalize(lightDir + reverseViewDir);
    float specReflectivity = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = dirLight.specularStrength * specReflectivity * dirLight.color;

    return diffuse + specular;
}

// Spot Light Calculation
vec3 calculateSpotLight(vec3 norm, vec3 fragPos, vec3 reverseViewDir)
{
    // Direction from the Fragment to the Spot Light source
    vec3 lightDir = normalize(spotLight.position - fragPos);

    // -- Spot Light Cone Calculation -- //
    // Angle between the 'Fragment to Spot Light' Direction and the Spot Light's aim direction
    float theta = dot(lightDir, normalize(-spotLight.direction));

    // Smooth Fading Intensity between Inner and Outer Cone
    float epsilon = spotLight.innerCutoffAngle - spotLight.outerCutoffAngle;
    float intensity = clamp((theta - spotLight.outerCutoffAngle) / epsilon, 0.0, 1.0);
    // -- //

    // Diffuse
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * spotLight.color;

    // Specular
    vec3 halfwayDir = normalize(lightDir + reverseViewDir);
    float specReflectivity = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = spotLight.specularStrength * specReflectivity * spotLight.color;

    // Apply Intensity to Diffuse and Specular for the Fading
    diffuse  *= intensity;
    specular *= intensity;

    return diffuse + specular;
}
// -- //



// -- Main -- //
void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 reverseViewDir = normalize(cameraPosition - fragWorldPosition); // Direction from the Fragment to Camera View

    // Ambient applied once for Global Illumination
    vec3 ambient = ambientStrength * ambientColor;
    vec3 totalLight = ambient;

    // Add all the Point Lights
    if (pointLightsEnabled) {
        for (int i = 0; i < pointLightCount; i++) {
            totalLight += calculatePointLight(i, normal, fragWorldPosition, reverseViewDir);
        }
    }

    // Add the Directional Light
    if (dirLightEnabled) {
        totalLight += calculateDirectionalLight(normal, reverseViewDir);
    }

    // Add the Spot Light
    if (spotLightEnabled) {
        totalLight += calculateSpotLight(normal, fragWorldPosition, reverseViewDir);
    }

    vec4 texColor = texture(imageTexture, fragTexCoords);
    finalColor = vec4(totalLight, 1.0) * texColor;
}
// -- //