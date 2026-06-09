/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   CubeMapTexture.h
 Description :   Declares the CubeMapTexture Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <string>

/// <summary>
///		The texture for the skybox cube map.
/// </summary>
class CubeMapTexture {
private:
	// -- Cube Map Texture Properties -- //
	GLuint m_textureID;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="faces">
	///		A list of 6 file paths of image faces (in order):
	///		{ right, left, top, bottom, back, front }.
	/// </param>
	CubeMapTexture(const std::vector<std::string>& faces);

	/// <summary>
	///		Destructor.
	/// </summary>
	~CubeMapTexture();

	//==================================================
	// PRIMARY CUBE MAP TEXTURE METHODS
	//==================================================

	/// <summary>
	///		Active and bind the Texture to a Texture unit (slot) within the GPU.
	///		This enables shaders to sample and read the Texture during rendering.
	/// </summary>
	/// 
	/// <param name="slot">Slot to bind to.</param>
	void bind(GLuint slot) const;

	/// <summary>
	///		Unbinds the Texture from its Texture unit (slot) within the GPU,
	///		freeing up that slot.
	/// </summary>
	void unbind() const;

	/// <summary>
	///		Get the Texture ID stored in the GPU.
	/// </summary>
	/// 
	/// <returns>
	///		Texture ID.
	/// </returns>
	GLuint getTextureID() const;
};

