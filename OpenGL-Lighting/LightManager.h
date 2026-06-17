/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   LightManager.h
 Description :   Declares the LightManager Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <string>

#include "Shader.h"
#include "Mesh.h"
#include "CameraFree.h"

/// <summary>
///     Point Light Struct.
/// </summary>
struct PointLight {
    // -- Light Properties -- //
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 color = glm::vec3(1.0f);
    float specularStrength = 1.0f;
    // -- //
    
    // -- Attenuation -- //
    float attenuationConst = 1.0f;
    float attenuationLinear = 0.045f;
    float attenuationExponent = 0.0075f;
    // -- //
};

/// <summary>
///     Directional Light Struct.
/// </summary>
struct DirectionalLight {
    // -- Light Properties -- //
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 color = glm::vec3(1.0f);
    float specularStrength = 1.0f;
    // -- //
};

/// <summary>
///     Spot Light Struct.
/// </summary>
struct SpotLight {
    // -- Light Properties -- //
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 color = glm::vec3(1.0f);
    float specularStrength = 1.0f;
    // -- //

    // -- Spot Light Cone -- //
    float innerCutoff = glm::cos(glm::radians(12.5f));
    float outerCutoff = glm::cos(glm::radians(17.5f));
    // -- //
};

/// <summary>
///     Light Manager class that manages any and all forms of lighting present in the world.
/// </summary>
class LightManager {
private:
    // -- Light Toggle Flags -- //
    bool m_pointLightsEnabled = true;
    bool m_dirLightEnabled = true;
    bool m_spotLightEnabled = true;
    // -- //

    // -- Point Lights -- //
    static const int MAX_POINT_LIGHTS = 4;
    PointLight m_pointLights[MAX_POINT_LIGHTS];
    int m_pointLightCount = 0;

    // Unlit Point Light Markers
    std::shared_ptr<Shader> m_unlitMarkerShader;
    std::shared_ptr<Mesh> m_unlitMarkerMesh;
    // -- //

    // -- Direction and Spot Light -- //
    DirectionalLight m_dirLight;
    SpotLight m_spotLight;
    // -- //

    // Ambient (global, not per-light)
    glm::vec3 m_ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
    float m_ambientStrength = 0.15f;

public:
    //==================================================
    // CONSTRUCTOR AND DESTRUCTOR
    //==================================================

    /// <summary>
    ///     Default constructor.
    /// </summary>
    LightManager() = default;

    /// <summary>
    ///     Default destructor.
    /// </summary>
    ~LightManager() = default;

    //==================================================
    // PRIMARY LIGHT MANAGER METHODS
    //==================================================

    /// <summary>
    ///     Initialise all the lights.
    /// </summary>
    void initialise();

    /// <summary>
    ///     Send all the lights to the shader.
    /// </summary>
    /// <param name="shader">Pointer to the shader to send all the lights to.</param>
    void sendToShader(Shader* shader);

    /// <summary>
    ///     Draw all the unlit markers.
    ///     IMPORTANT: This uses a different shader program.
    /// </summary>
    /// 
    /// <param name="camera">Reference to the Camera.</param>
    void drawUnlitMarkers(CameraFree& camera);

    /// <summary>
    ///     Handles the inputs for toggling each lights.
    /// </summary>
    void handleInputs();

    /// <summary>
    ///     Get a point light.
    /// </summary>
    /// 
    /// <param name="index">Index in the array.</param>
    /// 
    /// <returns>
    ///     A reference to a point light.
    /// </returns>
    PointLight& pointLight(const int& index);

    /// <summary>
    ///     Get a directional light.
    /// </summary>
    /// 
    /// <returns>
    ///     A reference to a directional light.
    /// </returns>
    DirectionalLight& directionalLight();

    /// <summary>
    ///     Get a spot light.
    /// </summary>
    /// 
    /// <returns>
    ///     A reference to a spot light.
    /// </returns>
    SpotLight& spotLight();
};