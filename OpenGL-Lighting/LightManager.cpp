/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   LightManager.cpp
 Description :   Defines the LightManager Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include <iostream>

#include "LightManager.h"
#include "InputHandler.h"

void LightManager::initialise() {
    this->m_unlitMarkerShader = std::make_shared<Shader>("Resources/Shaders/UnlitColor.vert", "Resources/Shaders/UnlitColor.frag");
    this->m_unlitMarkerMesh = std::make_shared<Mesh>("Resources/Models/Sphere_HighPoly.obj");

    // -- Point Light -- //
    // Red Point Light
    this->m_pointLights[0].position = glm::vec3(3.0f, 2.0f, 0.0f);
    this->m_pointLights[0].color = glm::vec3(1.0f, 0.3f, 0.3f);

    // Blue Point Light
    this->m_pointLights[1].position = glm::vec3(-3.0f, 2.0f, 2.0f);
    this->m_pointLights[1].color = glm::vec3(0.3f, 0.5f, 1.0f);

    // Point Light Count
    this->m_pointLightCount = 2;
    // -- //

    // Directional Light
    this->m_dirLight.color = glm::vec3(1.0f, 0.95f, 0.85f); // Warm White
}

void LightManager::sendToShader(Shader* shader) {
    // -- Ambient -- //
    shader->setVec3("ambientColor", this->m_ambientColor);
    shader->setFloat("ambientStrength", this->m_ambientStrength);
    // -- //

    // -- Toggle Light Bools -- //
    shader->setInt("pointLightsEnabled", this->m_pointLightsEnabled);
    shader->setInt("dirLightEnabled", this->m_dirLightEnabled);
    shader->setInt("spotLightEnabled", this->m_spotLightEnabled);
    // -- //

    // -- Point Lights -- //
    shader->setInt("pointLightCount", this->m_pointLightCount);

    // Loop per each Point Light
    for (int i = 0; i < this->m_pointLightCount; i++) {
        std::string base = "pointLights[" + std::to_string(i) + "].";

        // Point Light Properties
        shader->setVec3((base + "position"), this->m_pointLights[i].position);
        shader->setVec3((base + "color"), this->m_pointLights[i].color);
        shader->setFloat((base + "specularStrength"), this->m_pointLights[i].specularStrength);

        // Attenuation
        shader->setFloat((base + "attenuationConstant"), this->m_pointLights[i].attenuationConst);
        shader->setFloat((base + "attenuationLinear"), this->m_pointLights[i].attenuationLinear);
        shader->setFloat((base + "attenuationExponent"), this->m_pointLights[i].attenuationExponent);
    }
    // -- //

    // -- Directional Light -- //
    shader->setVec3("dirLight.direction", this->m_dirLight.direction);
    shader->setVec3("dirLight.color", this->m_dirLight.color);
    shader->setFloat("dirLight.specularStrength", this->m_dirLight.specularStrength);
    // -- //

    // -- Spot Light -- //
    // Spot Light Properties
    shader->setVec3("spotLight.position", this->m_spotLight.position);
    shader->setVec3("spotLight.direction", this->m_spotLight.direction);
    shader->setVec3("spotLight.color", this->m_spotLight.color);
    shader->setFloat("spotLight.specularStrength", this->m_spotLight.specularStrength);

    // Cone Properties
    shader->setFloat("spotLight.innerCutoffAngle", this->m_spotLight.innerCutoff);
    shader->setFloat("spotLight.outerCutoffAngle", this->m_spotLight.outerCutoff);
    // -- //
}

void LightManager::drawUnlitMarkers(CameraFree& camera) {
    // Bind to the Unlit Marker Shader
    this->m_unlitMarkerShader->use();

    // Loop through all the Point Lights
    for (int i = 0; i < this->m_pointLightCount; i++) {
        // Create a Model Matrix for the Marker
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, this->m_pointLights[i].position); // Translation based on the Position of the Point Light
        model = glm::scale(model, glm::vec3(1.0f)); // Scale

        // Send the MVP Matrices
        this->m_unlitMarkerShader->setMat4("matModel", model);
        this->m_unlitMarkerShader->setMat4("matView", camera.getCameraView());
        this->m_unlitMarkerShader->setMat4("matProjection", camera.getCameraPerspec());

        // Match the Color with the Color of the Point Light
        this->m_unlitMarkerShader->setVec3("objectColor", this->m_pointLights[i].color);

        // Draw the Unlit Marker Mesh
        this->m_unlitMarkerMesh->draw();
    }
}

void LightManager::handleInputs() {
    // Reference to the Input Handler
    InputHandler& input = InputHandler::getInstance();

    // Toggle Point Light
    if (input.wasKeyPressed(GLFW_KEY_1)) {
        this->m_pointLightsEnabled = !this->m_pointLightsEnabled;
        std::cout << "[LightManager] Point Lights " << (this->m_pointLightsEnabled ? "ON" : "OFF") << std::endl;
    }

    // Toggle Directional Light
    if (input.wasKeyPressed(GLFW_KEY_2)) {
        this->m_dirLightEnabled = !this->m_dirLightEnabled;
        std::cout << "[LightManager] Directional Light " << (this->m_dirLightEnabled ? "ON" : "OFF") << std::endl;
    }

    // Toggle Spot Light
    if (input.wasKeyPressed(GLFW_KEY_3)) {
        this->m_spotLightEnabled = !this->m_spotLightEnabled;
        std::cout << "[LightManager] Spot Light " << (this->m_spotLightEnabled ? "ON" : "OFF") << std::endl;
    }
}

PointLight& LightManager::pointLight(const int& index) {
    // Validate Index
    if (index > -1 && index < this->m_pointLightCount) {
        return this->m_pointLights[index];
    }
    else {
        std::cerr << "[LightManager] Point Light Index '" << index << "' was invalid!" << std::endl;
        throw;
    }
}

DirectionalLight& LightManager::directionalLight() {
    return this->m_dirLight;
}

SpotLight& LightManager::spotLight() {
    return this->m_spotLight;
}
