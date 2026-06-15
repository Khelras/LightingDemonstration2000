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
	// -- Test Entity -- // 
	this->m_entities.push_back(std::make_unique<Entity>(
		"Resources/Models/SM_Env_Statue_01.obj",
		"Resources/Shaders/Model.vert",
		"Resources/Shaders/Model.frag",
		"Resources/Textures/Dungeons_Texture_01.png"
	));

	this->m_entities[0]->setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
	this->m_entities[0]->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_entities[0]->setScale(glm::vec3(2.0f));
	// -- //

	// Scene Initialised
	std::cout << "[Scene] Initialised successfully." << std::endl;
}

void Scene::initialiseUI(float windowWidth, float windowHeight) {
	// TODO: initialise any UI elements here
}

std::vector<std::unique_ptr<Entity>>& Scene::getEntities() {
	return this->m_entities;
}

void Scene::update(float deltaTime) {
}

void Scene::render(CameraFree& camera) {
	for (auto& entity : this->m_entities) {
		entity->render(camera);
	}
}

