/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Material.h
 Description :   Declares the Material Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once

#include "Shader.h"
#include "Texture2D.h"

class Material {
private:
	// -- Material Properties -- //
	Shader* m_shader;
	Texture2D* m_texture;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor.
	/// </summary>
	Material();

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="shader">Pointer to the Shader.</param>
	/// <param name="texture">Pointer to the Texture2D.</param>
	Material(Shader* shader, Texture2D* texture);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Material();

	//==================================================
	// PRIMARY MATERIAL METHODS
	//==================================================

	/// <summary>
	///		Sets the material properties as uniforms in the shader.
	/// </summary>
	void apply() const ;
};

