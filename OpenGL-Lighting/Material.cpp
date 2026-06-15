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

Material::Material() {
	this->m_shader = nullptr;
	this->m_texture = nullptr;
}

Material::Material(Shader* shader, Texture2D* texture) {
	this->m_shader = shader;
	this->m_texture = texture;
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
