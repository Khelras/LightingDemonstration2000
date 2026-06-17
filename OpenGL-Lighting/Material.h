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
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture2D> m_texture;

	float m_shininess;
	float m_specularStrength;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="shader">Shared pointer to the Shader.</param>
	/// <param name="texture">Shared pointer to the Texture.</param>
	/// <param name="shininess">Determines the size and sharpness of the light; Default to 32.0f.</param>
	/// <param name="specularStrength">Determines the intensity or brightness of the light reflection; Default to 0.8f.</param>
	Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture2D> texture, float shininess = 32.0f, float specularStrength = 0.8f);

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
	void apply() const;

	/// <summary>
	///		Get the Shader.
	/// </summary>
	/// 
	/// <returns>
	///		The Shader of this Material as a raw pointer.
	/// </returns>
	Shader* getShader() const;

	/// <summary>
	///		Get the Texture.
	/// </summary>
	/// 
	/// <returns>
	///		The Texture of this Material as a raw pointer.
	/// </returns>
	Texture2D* getTexture() const;
};

