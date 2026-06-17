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

Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture2D> texture, float shininess, float specularStrength)
	: m_shader(shader), m_texture(texture), m_shininess(shininess), m_specularStrength(specularStrength) {}

Material::~Material() {
}

void Material::apply() const {
	// Check if a Shader does NOT Exist
	if (this->m_shader == nullptr) {
		return;
	}

	// Check if a Texture does Exist
	if (this->m_texture != nullptr) {
		this->m_texture->bind(GL_TEXTURE0);
		this->m_shader->setInt("imageTexture", 0);
	}

	// Shininess
	this->m_shader->setFloat("shininess", this->m_shininess);
}

Shader* Material::getShader() const {
	return this->m_shader.get();
}

Texture2D* Material::getTexture() const {
	return this->m_texture.get();
}
