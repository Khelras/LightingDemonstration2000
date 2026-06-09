/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Texture.cpp
 Description :   Defines the Texture Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture2D.h"

Texture2D::Texture2D() {
	this->m_textureID = 0;
	this->m_width = 0;
	this->m_height = 0;
	this->m_components = 0;

}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &this->m_textureID);
}

bool Texture2D::loadFromFile(const std::string& path, bool flip) {
	stbi_set_flip_vertically_on_load(flip);

	// Load the Image Data
	int imgWidth, imgHeight, imgComponents;
	unsigned char* imgData = stbi_load(path.c_str(), &imgWidth, &imgHeight, &imgComponents, 0);

	// Ensure the Image Data has successfully Loaded
	if (!imgData) {
		std::cout << "Failed to load texture from path: '" << path << "'!" << std::endl;
		return false;
	}

	// Save the Image Width, Height, and Components (Color Channels)
	this->m_width = imgWidth;
	this->m_height = imgHeight;
	this->m_components = imgComponents;

	// Create and Bind a new Texture Variable
	glGenTextures(1, &this->m_textureID);
	glBindTexture(GL_TEXTURE_2D, this->m_textureID);

	// Setting the Filtering, Mipmap, and Address Mode Parameters for this Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Enable Blending and set the Blend Function for Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Check how much Components the Load Image has
	GLint loadedComponents = (imgComponents == 4) ? GL_RGBA : GL_RGB; // RGBA or RGB Channels

	// Populate the Texture with the Image Data
	glTexImage2D(GL_TEXTURE_2D, 0, loadedComponents, imgWidth, imgHeight, 0, loadedComponents, GL_UNSIGNED_BYTE, imgData);

	// Generate the Mipmaps, Free the Memory, and Unbind the Texture
	glGenerateMipmap(GL_TEXTURE_2D); // Generate the Mipmaps for the currently bound Texture
	stbi_image_free(imgData); // Free the memory
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

	// Texture Loaded Successfully
	stbi_set_flip_vertically_on_load(!flip);
	return true;
}

void Texture2D::bind(GLuint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->m_textureID);
}

void Texture2D::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture2D::getTextureID() const {
	return this->m_textureID;
}

int Texture2D::getWidth() const {
	return this->m_width;
}

int Texture2D::getHeight() const {
	return this->m_height;
}

int Texture2D::getComponents() const {
	return this->m_components;
}
