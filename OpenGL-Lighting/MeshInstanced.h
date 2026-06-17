/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   MeshInstanced.h
 Description :   Declares the MeshInstanced Class functions and properties.
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once

#include "Mesh.h"

/// <summary>
///		Derives from the Mesh class to add an instanced draw buffer to allow for mass rendering in a single draw call.
///		Each Mesh will be draw with a randomised position, rotation, and scale.
/// </summary>
class MeshInstanced : public Mesh {
public:
	static const int INSTANCE_COUNT = 1000;

private:
    // -- Mesh Instanced Properties -- //
    GLuint m_instanceVBO;
    std::vector<glm::mat4> m_instanceMatrices;
    // -- //

public:
    //==================================================
    // CONSTRUCTORS AND DESTRUCTOR
    //==================================================

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// 
    /// <param name="filePath">File path to a '.obj' file.</param>
    MeshInstanced(const std::string& filePath);

    /// <summary>
    ///     Destructor.
    /// </summary>
    ~MeshInstanced();

    //==================================================
    // PRIMARY MESH INSTANCED METHODS
    //==================================================

    /// <summary>
    ///     Issue a single instanced draw call for all instances.
    /// </summary>
    void draw() override;

private:
    //==================================================
    // HELPER METHODS
    //==================================================

    /// <summary>
    ///     Generates model matrices with randomised position, rotation, and scale for each isntance.
    /// </summary>
    void generateInstanceMatrices();

    /// <summary>
    ///     Binds the instance VBO to the VAO from the base Mesh class.
    ///     This sets up the split Mat4 vertex attribute pointers in locations 3-6. 
    /// </summary>
    void setupInstanceBuffer();
};

