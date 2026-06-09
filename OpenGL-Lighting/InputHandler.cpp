/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   InputHandler.cpp
 Description :   Defines the InputHandler class
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include <iostream>

#include "InputHandler.h"

 // -- GLFW Static Callbacks -- //
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputHandler::getInstance().onKey(key, action);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    InputHandler::getInstance().onMouseButton(button, action);
}
// -- //

InputHandler& InputHandler::getInstance() {
    static InputHandler instance;
    return instance;
}

void InputHandler::initialise(GLFWwindow* window) {
    // Pointer to the GLFW Window
    this->m_window = window;

    // Register the static callbacks with GLFW
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

int InputHandler::getAxis(int positiveKey, int negativeKey) const {
    // Tri-Bool Pattern
    int positive = (glfwGetKey(this->m_window, positiveKey) == GLFW_PRESS) ? 1 : 0;
    int negative = (glfwGetKey(this->m_window, negativeKey) == GLFW_PRESS) ? 1 : 0;

    // Both held or neither held = 0
    // Only Positive = 1
    // Only Negative = -1
    return positive - negative;
}

bool InputHandler::isKeyHeld(int glfwKey) const {
    return glfwGetKey(this->m_window, glfwKey) == GLFW_PRESS;
}

bool InputHandler::wasKeyPressed(int glfwKey) const {
    // Only true for the single frame the key was first pressed
    auto it = this->m_keyPressedThisFrame.find(glfwKey);
    return (it != this->m_keyPressedThisFrame.end()) && it->second;
}

glm::vec2 InputHandler::getCursorPos() const {
    // Get the Mouse Position
    double dxPos, dyPos;
    glfwGetCursorPos(this->m_window, &dxPos, &dyPos);

    // Convert to Float
    float fxPos = static_cast<float>(dxPos);
    float fyPos = static_cast<float>(dyPos);

    // Return the 2D float vector for the mouse position
    return glm::vec2(fxPos, fyPos);
}

bool InputHandler::wasMouseButtonPressed(int glfwButton) const {
    // Only true for the single frame the button was first pressed
    auto it = this->m_mouseButtonPressedThisFrame.find(glfwButton);
    return (it != this->m_mouseButtonPressedThisFrame.end()) && it->second;
}

void InputHandler::onKey(int key, int action) {
    // The first Frame the Key was Physically Pressed
    if (action == GLFW_PRESS) {
        this->m_keyPressedThisFrame[key] = true;
    }
}

void InputHandler::onMouseButton(int button, int action) {
    // The first Frame the Button was Physically Pressed
    if (action == GLFW_PRESS) {
        this->m_mouseButtonPressedThisFrame[button] = true;
    }
}

void InputHandler::flush() {
    // Clear the single press states at end of the frame
    // This ensures that wasKeyPressed() and wasMouseButtonPressed() returns true for exactly ONE frame
    this->m_keyPressedThisFrame.clear();
    this->m_mouseButtonPressedThisFrame.clear();
}