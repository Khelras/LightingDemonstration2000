/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Mesh.h
 Description :   Declares the Mesh Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "ShaderLoader.h"

 //==================================================
 // VERTEX STRUCT
 //==================================================

 /// <summary>
 ///	A collection of position (xyz) and texture-coordinate (xy) vectors
 ///	which determines a vertex point of a shape.
 /// </summary>
struct Vertex {
	// -- Vertex Properties -- //
	glm::vec3 position;
	glm::vec2 texCoord;
	// -- //

	//==================================================
	// CONSTRUCTORS
	//==================================================

	/// <summary>
	///		Default Constructor.
	/// </summary>
	Vertex() {
		this->position = glm::vec3(0.0f);
		this->texCoord = glm::vec3(0.0f);
	};

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="position">3D position vector.</param>
	/// <param name="texCoord">2D texture coordinate vector.</param>
	Vertex(glm::vec3 position, glm::vec2 texCoord) {
		this->position = position;
		this->texCoord = texCoord;
	};
};



//==================================================
// MESH CLASS
//==================================================

/// <summary>
///		Mesh class which acts as a collection of vertices and indices 
///		that defines the shape or geometry of an object.
/// </summary>
class Mesh {
protected:
	// -- Mesh Geometry -- //
	std::vector<Vertex> m_vertices;
	// -- //

	// -- Mesh Properties -- //
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_drawCount;
	int m_drawType;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor
	/// </summary>
	Mesh();

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="filePath">File path to a '.obj' file.</param>
	Mesh(std::string filePath);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Mesh();

	//==================================================
	// PRIMARY MESH METHODS
	//==================================================

	/// <summary>
	///		Update the Mesh.
	/// </summary>
	/// 
	/// <param name="deltaTime">Delta Time as a float.</param>
	void update(float deltaTime);

	/// <summary>
	///		Renders the Mesh into the world.
	/// </summary>
	void draw();
};

