/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Camera.cpp
 Description :   Defines the Camera Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Camera.h"

Camera::Camera(float windowWidth, float windowHeight) {
	// -- Window Properties -- //
	this->m_windowWidth = windowWidth;
	this->m_windowHeight = windowHeight;
	// -- //

	// -- Default Camera View Properties -- //
	this->m_position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->m_lookDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->m_upDireciton = glm::vec3(0.0f, 1.0f, 0.0f);
	// -- //
}

Camera::~Camera() {
}

glm::mat4 Camera::getCameraView() {
	return glm::lookAt(this->m_position, this->m_position + this->m_lookDirection, this->m_upDireciton);
}

glm::mat4 Camera::getCameraOrtho() {
	// Origin Top-Left of the Screen
	return glm::ortho(0.0f, this->m_windowWidth, this->m_windowHeight, 0.0f, -1.0f, 1.0f);
}

glm::mat4 Camera::getCameraPerspec(float fov) {
	float aspectRatio = this->m_windowWidth / this->m_windowHeight;
	return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 500.0f);
}

glm::vec3 Camera::getCameraPosition() const {
	return this->m_position;
}

void Camera::setCameraPosition(glm::vec3 position) {
	this->m_position = position;
}

void Camera::setCameraLookDireciton(glm::vec3 direction) {
	this->m_lookDirection = direction;
}

void Camera::setCameraUpDirection(glm::vec3 direction) {
	this->m_upDireciton = direction;
}
