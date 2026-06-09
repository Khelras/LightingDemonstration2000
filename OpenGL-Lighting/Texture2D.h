/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Texture2D.h
 Description :   Declares the Texture2D Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include "Mesh.h"

 /// <summary>
 ///	Loads an image and store it as a Texture onto the GPU.
 /// </summary>
class Texture2D {
private:
	// -- Texture Properties -- //
	GLuint m_textureID;

	int m_width;
	int m_height;
	int m_components;
	// -- // 

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	Texture2D();

	/// <summary>
	///		Destructor.
	/// </summary>
	~Texture2D();

	//==================================================
	// PRIMARY TEXTURE METHODS
	//==================================================

	/// <summary>
	///		Loads an image using STB and create a Texture.
	/// </summary>
	/// 
	/// <param name="path">File path of image.</param>
	/// <param name="flip">Flip vertically on load. Defaulted to true.</param>
	/// 
	/// <returns>
	///		True if a Texture was successfully loaded.
	///		False otherwise.
	/// </returns>
	bool loadFromFile(const std::string& path, bool flip = true);

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

	//==================================================
	// GETTER METHODS
	//==================================================

	/// <summary>
	///		Get the Width of the original image texture.
	/// </summary>
	/// 
	/// <returns>
	///		Width of the original image texture in pixels.
	/// </returns>
	int getWidth() const;

	/// <summary>
	///		Get the Height of the original image texture.
	/// </summary>
	/// 
	/// <returns>
	///		Height of the original image texture in pixels.
	/// </returns>
	int getHeight() const;

	/// <summary>
	///		Get the Components (color channels) of the original image texture.
	/// </summary>
	/// 
	/// <returns>
	///		The total color channels of the original image texture.
	/// </returns>
	int getComponents() const;
};

