/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Scene.cpp
 Description :   Defines the Scene Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include <iostream>

#include "Scene.h"

Scene::Scene() {
	// Default to the Origin, have No Rotation, and have Normal Scale
	this->m_position = glm::vec3(0.0f);
	this->m_rotation = glm::vec3(0.0f); // degrees per axis
	this->m_scale = glm::vec3(1.0f);
}

Scene::~Scene() {
}

void Scene::initialise(const std::string& modelPath) {
	// Load 3D Model from the given File Path
	this->m_model = std::make_unique<Mesh>(modelPath);

	// Load the Texture
	this->m_texture = std::make_unique<Texture2D>();
	if (this->m_texture->loadFromFile("Resources/Textures/Dungeons_Texture_01.png") == false) {
		// Texture 1 Failed to Load
		std::cout << "[Scene] Failed to load texture 1: 'Resources/Textures/Dungeons_Texture_01.png'";
		std::cout << std::endl;
		exit(1);
	}

	// Start at the Origin, have No Rotation, and have Normal Scale
	this->m_position = glm::vec3(0.0f);
	this->m_rotation = glm::vec3(0.0f);
	this->m_scale = glm::vec3(1.0f);

	// Six Skybox Face Images in the Order: +X, -X, +Y, -Y, +Z, -Z
	this->m_skybox = std::make_unique<Skybox>(std::vector<std::string>{
		"Resources/Textures/Skybox/Right.png",		// +X
		"Resources/Textures/Skybox/Left.png",		// -X
		"Resources/Textures/Skybox/Top.png",		// +Y
		"Resources/Textures/Skybox/Bottom.png",		// -Y
		"Resources/Textures/Skybox/Back.png",		// +Z
		"Resources/Textures/Skybox/Front.png"		// -Z
	});

	// Initialise the Skybox
	this->m_skybox->initialise();

	// Reflection Map Texture
	this->m_reflectionMap = std::make_unique<Texture2D>();

	// Check if the Reflection Map Texture Loaded Succesfully
	if (this->m_reflectionMap->loadFromFile("Resources/Textures/ReflectionMap.png") == false) {
		std::cout << "[Scene] Failed to load reflection map texture: 'Resources/Textures/ReflectionMap.png'" << std::endl;
		exit(1);
	};

	// Scene Initialised
	std::cout << "[Scene] Initialised successfully. Model: '" << modelPath << std::endl;
}

void Scene::initialiseUI(float windowWidth, float windowHeight) {
	// TODO: initialise any UI elements here
}

void Scene::update(float deltaTime) {
}

void Scene::moveObject(glm::vec3 delta) {
	this->m_position += delta * this->m_moveSpeed;
}

Mesh* Scene::getModel() const {
	return this->m_model.get();
}

Texture2D* Scene::getTexture() const {
	return this->m_texture.get();
}

Skybox* Scene::getSkybox() const {
	return this->m_skybox.get();
}

Texture2D* Scene::getReflectionMap() const {
	return this->m_reflectionMap.get();
}

glm::vec3 Scene::getPosition() const {
	return this->m_position;
}

glm::vec3 Scene::getRotation() const {
	return this->m_rotation;
}

glm::vec3 Scene::getScale() const {
	return this->m_scale;
}

glm::mat4 Scene::getModelMatrix() const {
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

void Scene::setPosition(glm::vec3 position) {
	this->m_position = position;
}

void Scene::setRotation(glm::vec3 rotation) {
	this->m_rotation = rotation;
}

void Scene::setScale(glm::vec3 scale) {
	this->m_scale = scale;
}
