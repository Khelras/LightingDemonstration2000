/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   CubeMapTexture.cpp
 Description :   Defines the CubeMapTexture Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include <stb_image.h>
#include <iostream>

#include "CubeMapTexture.h"

CubeMapTexture::CubeMapTexture(const std::vector<std::string>& faces) {
	glGenTextures(1, &this->m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textureID);

	// Cube Maps expect the Origin (0, 0) to be Top-Left (Opposite from Standard Textres)
	stbi_set_flip_vertically_on_load(false);

	// Loop through each Face and Load the Image Data
	int imgWidth, imgHeight, imgComponents;
	for (unsigned int i = 0; i < faces.size(); i++) {
		// Load the Image Data
		unsigned char* imgData = stbi_load(faces[i].c_str(), &imgWidth, &imgHeight, &imgComponents, 0);

		// Ensure the Image Data has Successfully Loaded
		if (imgData) {
			std::cout << "[CubeMapTexture] Face " << i << " loaded: " << faces[i];
			std::cout << " (" << imgWidth << "x" << imgHeight << ")" << std::endl;

			// Check how much Components the Load Image has
			GLint loadedComponents = (imgComponents == 4) ? GL_RGBA : GL_RGB; // RGBA or RGB Channels

			// Populate the Texture with the Image Data
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
				loadedComponents, imgWidth, imgHeight, 0, loadedComponents, GL_UNSIGNED_BYTE, imgData);
		}
		else {
			// Image Failed to Load
			std::cerr << "[CubeMapTexture] Failed to load face from path: '" << faces[i] << "'" << std::endl;
		}

		// Free the Data Per Face
		stbi_image_free(imgData);
	}

	// Setting the address mode of this Texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate the Mipmaps and Unbind the Texture
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP); // Generate the Mipmaps for the currently bound Texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // Unbind the texture
	stbi_set_flip_vertically_on_load(true); // Restore Flip for Standard Textures
}

CubeMapTexture::~CubeMapTexture() {
	glDeleteTextures(1, &this->m_textureID);
}

void CubeMapTexture::bind(GLuint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textureID);
}

void CubeMapTexture::unbind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint CubeMapTexture::getTextureID() const {
	return this->m_textureID;
}
