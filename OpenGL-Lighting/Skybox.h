/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Skybox.h
 Description :   Declares the Skybox Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glm.hpp>
#include <memory>

#include "ShaderLoader.h"
#include "CubeMapTexture.h"

class Skybox {
private:
	// -- VAOs, VBOs, EBOs -- //
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	// -- //

	// -- Skybox Properties -- //
	GLuint m_program;
	std::unique_ptr<CubeMapTexture> m_cubeMap;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor.
	/// </summary>
	Skybox();

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="faces">
	///		A list of 6 file paths of image faces (in order):
	///		{ right, left, top, bottom, back, front }.
	/// </param>
	Skybox(const std::vector<std::string>& faces);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Skybox();

	//==================================================
	// PRIMARY SKYBOX METHODS
	//==================================================

	/// <summary>
	///		Initialise the Scene.
	/// </summary>
	void initialise();

	/// <summary>
	///		Render the Skybox into the world.
	/// </summary>
	/// 
	/// <param name="view">4x4 camera view matrix.</param>
	/// <param name="projection">4x4 camera projection matrix.</param>
	void draw(const glm::mat4& view, const glm::mat4& projection);

	//==================================================
	// PRIMARY SKYBOX METHODS
	//==================================================

	/// <summary>
	///		Get the Cube Map Texture.
	/// </summary>
	/// 
	/// <returns>
	///		Cube Map Texture.
	/// </returns>
	CubeMapTexture* getCubeMap() const;
};

