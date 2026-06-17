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
}

Scene::~Scene() {
}

void Scene::initialise() {
	// Initialise the Lights
	this->m_lightManager.initialise();

	// Shader
	this->m_shader = std::make_shared<Shader>("Resources/Shaders/BlinnPhong.vert", "Resources/Shaders/BlinnPhong.frag");

	// Texture
	this->m_texture = std::make_shared<Texture2D>();
	this->m_texture->loadFromFile("Resources/Textures/Dungeons_Texture_01.png");

	// Mesh
	this->m_mesh = std::make_shared<Mesh>("Resources/Models/SM_Env_Statue_01.obj");

	// Material
	this->m_material = std::make_shared<Material>(this->m_shader, this->m_texture);

	// -- Load Entities -- // 
	this->m_entities.emplace_back(this->m_mesh, this->m_material);
	this->m_entities[0].setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
	this->m_entities[0].setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_entities[0].setScale(glm::vec3(2.0f));
	// -- //

	// Scene Initialised
	std::cout << "[Scene] Initialised successfully." << std::endl;
}

void Scene::initialiseUI(float windowWidth, float windowHeight) {
	// TODO: initialise any UI elements here
}

std::vector<Entity>& Scene::getEntities() {
	return this->m_entities;
}

void Scene::handleInputs() {
	this->m_lightManager.handleInputs();
}

void Scene::update(float deltaTime) {
}

void Scene::render(CameraFree& camera) {
	// Spot Light to Follow the Free Camera
	this->m_lightManager.spotLight().position = camera.getCameraPosition();
	this->m_lightManager.spotLight().direction = camera.getCameraForward();

	// Bind to the Shader
	this->m_shader->use();

	// Send the Light Data
	this->m_lightManager.sendToShader(this->m_shader.get());

	// Send the Camera Position
	this->m_shader->setVec3("cameraPosition", camera.getCameraPosition());

	// Draw all the Entities
	for (auto& entity : this->m_entities) {
		entity.draw(camera);
	}
}

