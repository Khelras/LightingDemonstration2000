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
};

static void cursorPositionCallback(GLFWwindow*, double xPos, double yPos) {
    InputHandler::getInstance().onCursorMove(static_cast<float>(xPos), static_cast<float>(yPos));
}

static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	InputHandler::getInstance().onScroll(static_cast<float>(yOffset));
}
// -- //

InputHandler& InputHandler::getInstance() {
    static InputHandler instance;
    return instance;
}

void InputHandler::initialise(GLFWwindow* window) {
    // Pointer to the GLFW Window
    this->m_window = window;

    // Enable the 'Disabled Cursor' Mode to hide the Cursour and Capture the Mouse Movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Register the static callbacks with GLFW
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetScrollCallback(window, scrollCallback);
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

void InputHandler::getCursorPosition(float& x, float& y) const {
    x = this->m_cursorPositionX;
    y = this->m_cursorPositionY;
}

float InputHandler::getScrollOffsetY() const {
    return this->m_scrollOffsetY;
}

bool InputHandler::isKeyHeld(int glfwKey) const {
    return glfwGetKey(this->m_window, glfwKey) == GLFW_PRESS;
}

bool InputHandler::wasKeyPressed(int glfwKey) const {
    // Only true for the single frame the key was first pressed
    auto it = this->m_keyPressedThisFrame.find(glfwKey);
    return (it != this->m_keyPressedThisFrame.end()) && it->second;
}

bool InputHandler::wasMouseButtonPressed(int glfwButton) const {
    // Only true for the single frame the button was first pressed
    auto it = this->m_mouseButtonPressedThisFrame.find(glfwButton);
    return (it != this->m_mouseButtonPressedThisFrame.end()) && it->second;
}

void InputHandler::flush() {
    // Clear the single press states at end of the Frame
    // This ensures that wasKeyPressed() and wasMouseButtonPressed() returns true for exactly ONE frame
    this->m_keyPressedThisFrame.clear();
    this->m_mouseButtonPressedThisFrame.clear();
    
    // Reset the Scroll Y-Offset at the end of the Frame
    this->m_scrollOffsetY = 0.0f;
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

void InputHandler::onCursorMove(float xPosition, float yPosition) {
    this->m_cursorPositionX = xPosition;
	this->m_cursorPositionY = yPosition;
}

void InputHandler::onScroll(float yOffset) {
    this->m_scrollOffsetY = yOffset;
}
