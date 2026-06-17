/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Entity.cpp
 Description :   Declares the Entity Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Entity.h"

Entity::Entity(std::shared_ptr<MeshInstanced> mesh, std::shared_ptr<Material> material) : m_mesh(mesh), m_material(material) {
	// Default Transform Properties
	this->m_position = glm::vec3(0.0f);
	this->m_rotation = glm::vec3(0.0f);
	this->m_scale = glm::vec3(1.0f);
}

Entity::~Entity() {
}

void Entity::draw(CameraFree& camera) const {
	// Apply the Material of the Entity
	this->m_material->apply();
	
	// MVP (Model, View, Projection) Matrices and Camera Position
	glm::mat4 model = this->getModelMatrix();
	glm::mat4 view = camera.getCameraView();
	glm::mat4 projection = camera.getCameraPerspec();

	// Send the MVP Matrices
	this->m_material->getShader()->setMat4("matModel", model);
	this->m_material->getShader()->setMat4("matView", view);
	this->m_material->getShader()->setMat4("matProjection", projection);

	// Draw the Mesh Model
	this->m_mesh->draw();
}

Mesh* Entity::getModel() const {
	return this->m_mesh.get();
}

Material* Entity::getMaterial() const {
	return this->m_material.get();
}

glm::vec3 Entity::getPosition() const {
	return this->m_position;
}

glm::vec3 Entity::getRotation() const {
	return this->m_rotation;
}

glm::vec3 Entity::getScale() const {
	return this->m_scale;
}

glm::mat4 Entity::getModelMatrix() const {
	// Construct a Translation, Rotation, and Scale Matrices from the Transformation Properties.
	glm::mat4 matTranslation, matRotation, matScale;
	matTranslation = glm::translate(glm::mat4(1.0f), this->m_position);
	matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	matRotation = glm::rotate(matRotation, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	matRotation = glm::rotate(matRotation, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	matScale = glm::scale(glm::mat4(1.0f), this->m_scale);

	// Calculate the Model Matrix by multiplying the Translation, Rotation, and Scale Matrices together in that order.
	// This will apply the Transformations in this order: Scale -> Rotate -> Translate.
	return (matTranslation * matRotation * matScale);
}

void Entity::setPosition(glm::vec3 position) {
	this->m_position = position;
}

void Entity::setRotation(glm::vec3 rotation) {
	this->m_rotation = rotation;
}

void Entity::setScale(glm::vec3 scale) {
	this->m_scale = scale;
}