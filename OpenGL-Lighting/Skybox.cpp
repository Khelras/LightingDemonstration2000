/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Skybox.cpp
 Description :   Defines the Skybox Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include <gtc/type_ptr.hpp>

#include "Skybox.h"

// Skybox Cube Map Vertices 
float skyboxVertices[] = {
    // Position (X, Y, Z) Only Vertices
    -1.0f,  1.0f,  1.0f,    -1.0f, -1.0f,  1.0f,     1.0f, -1.0f,  1.0f,     1.0f,  1.0f,  1.0f,    // Front Quad
     1.0f,  1.0f, -1.0f,     1.0f, -1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f,  1.0f, -1.0f,    // Back Quad
     1.0f,  1.0f,  1.0f,     1.0f, -1.0f,  1.0f,     1.0f, -1.0f, -1.0f,     1.0f,  1.0f, -1.0f,    // Right Quad
    -1.0f,  1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,    -1.0f,  1.0f,  1.0f,    // Left Quad
    -1.0f,  1.0f, -1.0f,    -1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,     1.0f,  1.0f, -1.0f,    // Top Quad
    -1.0f, -1.0f,  1.0f,    -1.0f, -1.0f, -1.0f,     1.0f, -1.0f, -1.0f,     1.0f, -1.0f,  1.0f     // Bottom Quad
};

// Skybox Cube Map Indices
unsigned int skyboxIndices[] = {
    /* Right  Triangle-1 */  0,  1,  2,    /* Right  Triangle-2 */  0,  2,  3,
    /* Left   Triangle-1 */  4,  5,  6,    /* Left   Triangle-2 */  4,  6,  7,
    /* Top    Triangle-1 */  8,  9, 10,    /* Top    Triangle-2 */  8, 10, 11,
    /* Bottom Triangle-1 */ 12, 13, 14,    /* Bottom Triangle-2 */ 12, 14, 15,
    /* Front  Triangle-1 */ 16, 17, 18,    /* Front  Triangle-2 */ 16, 18, 19,
    /* Back   Triangle-1 */ 20, 21, 22,    /* Back   Triangle-2 */ 20, 22, 23,
};

Skybox::Skybox() {
	this->m_vao = 0;
	this->m_vbo = 0;
	this->m_ebo = 0;
	this->m_program = 0;
}

Skybox::Skybox(const std::vector<std::string>& faces) : Skybox() {
    this->m_cubeMap = std::make_unique<CubeMapTexture>(faces);
}

Skybox::~Skybox() {
}

void Skybox::initialise() {
    // Create the Skybox Shader Program
    this->m_program = ShaderLoader::CreateProgram("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag");

    // Generate the VAO
    glGenVertexArrays(1, &this->m_vao);
    glBindVertexArray(this->m_vao);

    // Generate the EBO
    glGenBuffers(1, &this->m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

    // Generate the VBO 
    glGenBuffers(1, &this->m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    // Set the Vertex Attribute information (Position Only)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Unbind the VAO
    glBindVertexArray(0);
}

void Skybox::draw(const glm::mat4& view, const glm::mat4& projection) {
    // Bind the Skybox Shader Program
    glUseProgram(this->m_program);

    // Remove the Translation from the View Matrix
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));

    // Send the VP Matrices to the Skybox Shader Program via Uniforms
    glUniformMatrix4fv( // View Matrix
        glGetUniformLocation(this->m_program, "matView"), 1, GL_FALSE, glm::value_ptr(viewNoTranslation)); 
    glUniformMatrix4fv( // Projection Matrix
        glGetUniformLocation(this->m_program, "matProjection"), 1, GL_FALSE, glm::value_ptr(projection)); 

    // Bind the Skybox Cube Map Texture to Slot 0
    this->getCubeMap()->bind(0);
    glUniform1i(glGetUniformLocation(this->m_program, "textureSkybox"), 0);

    // Render the Skybox Mesh
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL); // Depth
    glBindVertexArray(m_vao); // Bind the VAO
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    // Unbind the Texture
    this->m_cubeMap->unbind();

    // Unbind the Program
    glUseProgram(0);
}

CubeMapTexture* Skybox::getCubeMap() const {
    return this->m_cubeMap.get();
}
