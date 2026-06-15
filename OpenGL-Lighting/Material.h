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
#include <memory>

#include "Shader.h"
#include "Texture2D.h"

/// <summary>
///		Material class that encapsulates a Shader with Textures.
/// </summary>
class Material {
private:
	// -- Material Properties -- //
	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Texture2D> m_texture;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="vertexPath">File path to the vertex shader.</param>
	/// <param name="fragmentPath">File path to the fragment shader.</param>
	/// <param name="texturePath">File path to the texture.</param>
	Material(const char* vertexPath, const char* fragmentPath, const std::string& texturePath);

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

