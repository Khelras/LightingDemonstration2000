/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Material.cpp
 Description :   Defines the Material Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Material.h"

Material::Material(const char* vertexPath, const char* fragmentPath, const std::string& texturePath) {
	this->m_shader = std::make_unique<Shader>(vertexPath, fragmentPath);
	this->m_texture = std::make_unique<Texture2D>();
	this->m_texture->loadFromFile(texturePath);
}

Material::~Material() {
}

void Material::apply() const {
	// Check if a Shader does NOT Exist
	if (this->m_shader == nullptr) {
		return;
	}

	// Use the Shader
	this->m_shader->use();

	// Check if a Texture does Exist
	if (this->m_texture != nullptr) {
		this->m_texture->bind(GL_TEXTURE0);
		this->m_shader->setInt("texture0", 0);
	}
}
