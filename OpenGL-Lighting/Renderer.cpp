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
}

Renderer::~Renderer() {
}

void Renderer::initialise() {
    // Depth Testing to Render Faces in the correct order
    glEnable(GL_DEPTH_TEST);

    // Back Face Culling to skip Invisible Faces which improves performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::render(Scene& scene, CameraFree& camera) {
    // Clear the back buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the Entities of the Scene
    scene.render(camera);

    // Unbind the Program
    glUseProgram(0);
}
