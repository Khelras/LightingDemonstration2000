/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   CameraFree.cpp
 Description :   Defines the CameraFree Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "CameraFree.h"
#include "InputHandler.h"

CameraFree::CameraFree(float windowWidth, float windowHeight) : Camera(windowWidth, windowHeight) {
	// Default Free Camera Properties
	this->m_movementSpeed = 5.0f;
	this->m_mouseSensitivity = 0.1f;
}

CameraFree::~CameraFree() {
}

void CameraFree::handleFreeCameraMovement(float deltaTime) {
	// Reference to the Input Handler
	InputHandler& input = InputHandler::getInstance();

	// Direction Vectors in Relation the Camera
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f); // World Upwards Direction (+Y)
	glm::vec3 forward = glm::normalize(this->m_lookDirection); // Forward Vector based on the Look Direction
	glm::vec3 right = glm::normalize(glm::cross(forward, worldUp)); // Perpendicular to the Forward Vector

	// Tri-Bool Axis for WASD + QE Movement
	int depth = input.getAxis(GLFW_KEY_W, GLFW_KEY_S); // W and S
	int horizontal = input.getAxis(GLFW_KEY_D, GLFW_KEY_A); // A and D
	int vertical = input.getAxis(GLFW_KEY_Q, GLFW_KEY_E); // Q and E

	// Construct the Delta Movement Vector
	glm::vec3 movement = glm::vec3(0.0f);
	movement += static_cast<float>(horizontal) * right; // Right and Left
	movement += static_cast<float>(depth) * forward; // Forward and Backward
	movement += static_cast<float>(vertical) * worldUp; // Up and Down

	// Normalize so Diagonal Movement is NOT Faster
	if (glm::length(movement) > 0.0f) movement = glm::normalize(movement);

	// Apply the Movement
	this->m_position += movement * this->m_movementSpeed * deltaTime;
}

void CameraFree::setMovementSpeed(float speed) {
	this->m_movementSpeed = speed;
}

void CameraFree::setMouseSensitivity(float sensitivity) {
	this->m_mouseSensitivity = sensitivity;
}
