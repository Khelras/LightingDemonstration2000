/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Renderer.cpp
 Description :   Defines the Renderer Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Renderer.h"

Renderer::Renderer() {
    this->m_program = 0;
    this->m_wireframeActive = false;
}

Renderer::~Renderer() {
}

void Renderer::initialise(const std::string& vertPath, const std::string& fragPath) {
    // Create the Shader Program
    this->m_program = ShaderLoader::CreateProgram(vertPath.c_str(), fragPath.c_str());

    // Depth Testing to Render Faces in the correct order
    glEnable(GL_DEPTH_TEST);

    // Back Face Culling to skip Invisible Faces which improves performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::render(const Scene& scene, CameraFree& camera) {
    /*
        Rendering Steps (occurs per frame):
            1. Clear the back buffer
            2. Process any relevant Render Logic
            3. Draw/Render to the back buffer
    */

    // -- Step 1: Clear the back buffer -- //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // -- //



    // -- Step 2: Process any relevant Render Logic -- //
    // Bind the Shader Program
    glUseProgram(this->m_program);

    // MVP (Model, View, Projection) Matrices and Camera Position
    glm::mat4 model = scene.getModelMatrix();
    glm::mat4 view = camera.getCameraView();
    glm::mat4 projection = camera.getCameraPerspec();
    glm::vec3 cameraPosition = camera.getCameraPosition();

    // Send the MVP Matrices and the Camera Position to the Shader Program via Uniforms
    glUniformMatrix4fv(glGetUniformLocation(this->m_program, "matModel"), 1, GL_FALSE, glm::value_ptr(model)); // Model Matrix
    glUniformMatrix4fv(glGetUniformLocation(this->m_program, "matView"), 1, GL_FALSE, glm::value_ptr(view)); // View Matrix
    glUniformMatrix4fv(glGetUniformLocation(this->m_program, "matProjection"), 1, GL_FALSE, glm::value_ptr(projection)); // Projection Matrix
    glUniform3fv(glGetUniformLocation(this->m_program, "cameraPosition"), 1, glm::value_ptr(cameraPosition));

    // Bind the Scene's 3D Object Texture to Slot 0
    scene.getTexture()->bind(0);
    glUniform1i(glGetUniformLocation(this->m_program, "texture0"), 0);
    // -- // 



    // -- Step 3: Draw/Render to the back buffer -- //
    // Render the Model Mesh
    scene.getModel()->draw();   

    // Unbind the Textures
    scene.getTexture()->unbind();

    // Unbind the Program
    glUseProgram(0);
    // -- //
}

void Renderer::toggleWireframe() {
    // Toggle the Wireframe
    this->m_wireframeActive = !this->m_wireframeActive;
    if (this->m_wireframeActive) {
        // Wireframe On
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        // Wireframe Off
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Log to Console
    std::cout << "[Renderer] Wireframe " << (this->m_wireframeActive ? "ON" : "OFF") << std::endl;
}
