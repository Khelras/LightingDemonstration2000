/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   MeshInstanced.cpp
 Description :   Defines the MeshInstanced Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include <cstdlib>
#include <ctime>

#include "MeshInstanced.h"

// Static Helper RNG with Min and Max
static float randFloat(float min, float max) {
	return min + (static_cast<float>(std::rand()) / RAND_MAX) * (max - min);
}

MeshInstanced::MeshInstanced(const std::string& filePath) : Mesh(filePath), m_instanceVBO(0) {
	// Seed the RNG to the Time
	srand(static_cast<unsigned>(time(nullptr)));

    // Generate and the Setup the Instance Matrices
	this->generateInstanceMatrices();
	this->setupInstanceBuffer();
}

MeshInstanced::~MeshInstanced() {
}

void MeshInstanced::draw() {
    glBindVertexArray(this->m_vao);
    glDrawArraysInstanced(this->m_drawType, 0, this->m_drawCount, INSTANCE_COUNT);
    glBindVertexArray(0);
}

void MeshInstanced::generateInstanceMatrices() {
    this->m_instanceMatrices.clear();
    this->m_instanceMatrices.reserve(INSTANCE_COUNT);

    for (int i = 0; i < INSTANCE_COUNT; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        // Random position spread across a large flat area
        float x = randFloat(-50.0f, 50.0f);
        float y = 0.0f;
        float z = randFloat(-50.0f, 50.0f);
        model = glm::translate(model, glm::vec3(x, y, z));

        // Random Y rotation (full 360) + subtle X tilt
        model = glm::rotate(model, glm::radians(randFloat(0.0f, 360.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(randFloat(-10.0f, 10.0f)), glm::vec3(1.0f, 0.0f, 0.0f));

        // Random uniform scale — kept reasonable so all instances are visible
        float scale = randFloat(0.5f, 2.0f);
        model = glm::scale(model, glm::vec3(scale));

        this->m_instanceMatrices.push_back(model);
    }
}

void MeshInstanced::setupInstanceBuffer() {
    // Bind to the VAO from the Base Mesh Class
    glBindVertexArray(this->m_vao);

    // Create a new VBO specifically for the Instance Matrices
    glGenBuffers(1, &this->m_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, INSTANCE_COUNT * sizeof(glm::mat4), m_instanceMatrices.data(), GL_DYNAMIC_DRAW);

    // A 4x4 Matrix is 4 x 4D Vectors.
    // Each Column needs its own Vertex Attribute Location (as we cannot just pass in a Mat4).
    // Therefore, we need to pass in 4 x 4D Vectors at Locations 3, 4, 5, 6
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(3); // Column 1
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4); // Column 2
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5); // Column 3
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6); // Column 4

    // Divisor of 1 means that the Vertex Attributes advance once per INSTANCE and not per Vector
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    // Unbind the VAO
    glBindVertexArray(0);
}
