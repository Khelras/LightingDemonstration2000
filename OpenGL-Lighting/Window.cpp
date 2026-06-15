/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Window.cpp
 Description :   Declares the Window Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Window.h"
#include "InputHandler.h"

Window::Window(unsigned int width, unsigned int height) {
	// -- Window Properties -- //
	this->m_window = nullptr;
	this->m_windowWidth = width;
	this->m_windowHeight = height;
	this->m_cursorVisible = true;

	this->m_camera = std::make_unique<CameraFree>(static_cast<float>(width), static_cast<float>(height));
	this->m_scene = std::make_unique<Scene>();
	this->m_renderer = std::make_unique<Renderer>();
	// -- //

	// -- Time -- //
	this->m_currentTime = 0.0f;
	this->m_previousTime = 0.0f;
	this->m_deltaTime = 0.0f;
	// -- // 
}

Window::~Window() {
	// Delete Window
	if (this->m_window != nullptr) {
		glfwDestroyWindow(this->m_window);
		this->m_window = nullptr;
	}
}

bool Window::initialize(int major, int minor) {
	// Check if Window already exists
	if (this->m_window != nullptr) {
		// Prevent from re-initialising the Window
		std::cout << "A window has already been initialised!" << std::endl;
		return false;
	}

	// Initializing GLFW and setting the version to the given major and minor with compatibility profile
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Sets the OpenGL profile to compatibility mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); // Sets the major version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); // Sets the minor version of OpenGL

	// Create an GLFW controlled context window
	this->m_window = glfwCreateWindow(this->m_windowWidth, this->m_windowHeight, "Epic OpenGL Project 2000", NULL, NULL);

	// Check if the window was created successfully
	if (this->m_window == NULL) {
		// Print an error message
		std::cout << "Window failed to create. Terminating program." << std::endl;

		// Retrieve and print the error message from GLFW
		const char* description;
		int code = glfwGetError(&description);
		if (description) {
			printf("Error [%d]: %s\n", code, description);
		}

		system("pause"); // Pause the console to allow the user to read the error message
		glfwTerminate(); // Destroy all the remaining windows and cursors, and free any other allocated resources
		return false; // Return false to indicate an error occurred
	}

	// Make the context of the window the main context on the current calling thread
	glfwMakeContextCurrent(this->m_window);

	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK) { // Check if GLEW was initialized successfully
		std::cout << "GLEW failed to initialize properly. Terminating program." << std::endl; // Print an error message
		system("pause"); // Pause the console to allow the user to read the error message
		glfwTerminate(); // Destroy all the remaining windows and cursors, and free any other allocated resources
		return false; // Return false to indicate an error occurred
	}

	// Set the clear color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // RGBA values

	// Set the viewport to cover the entire window
	glViewport(0, 0, this->m_windowWidth, this->m_windowHeight);

	// Initialise the Input Handler
	InputHandler::getInstance().initialise(this->m_window);

	// Initialise the Scene and the Renderer
	this->m_scene->initialise();
	//this->m_scene->initialiseUI(static_cast<float>(this->m_windowWidth), static_cast<float>(this->m_windowHeight));
	//this->m_scene->setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
	//this->m_scene->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	//this->m_scene->setScale(glm::vec3(2.0f));
	this->m_renderer->initialise();
	std::cout << std::endl;

	// Initialisation was a success, returning true
	return true;
}

bool Window::process() {
	// Main loop, runs until the end of the program
	if (glfwWindowShouldClose(this->m_window) == false) { // Check if Window should close
		// Poll for Events
		this->pollEvents();

		// Update all objects and run the processes
		this->update();

		// Render all the Objects
		this->render();

		// Flush the Single Press Hash Maps at the very end of the Frame
		InputHandler::getInstance().flush();

		// Continue process
		return true;
	}
	else {
		// Window is closed, end process
		return false;
	}
}

void Window::pollEvents() {
	// Poll for and process events
	glfwPollEvents();

	// Handle Free Camera Movement
	this->m_camera->handleFreeCameraMovement(this->m_deltaTime);

	// Reference to the Input Handler
	InputHandler& input = InputHandler::getInstance();

	// Escape-Key Pressed
	if (input.wasKeyPressed(GLFW_KEY_ESCAPE)) { // Shutdown the Window
		// Set Window to Close
		glfwSetWindowShouldClose(this->m_window, true);

		// Log to Console
		std::cout << "[Window] Shutting down..." << std::endl;
	}
}

void Window::update() {
	// Update the Current, Last, and Delta Times
	this->m_currentTime = (float)glfwGetTime();
	this->m_deltaTime = this->m_currentTime - this->m_previousTime;
	this->m_previousTime = this->m_currentTime;
}

void Window::render() {
	// Render
	this->m_renderer->render(*this->m_scene.get(), *this->m_camera.get());

	// Swap the Front and Back Buffers
	glfwSwapBuffers(this->m_window);
}

void Window::toggleCursorVisibility() {
	// Togle the Cursor Visibilty
	this->m_cursorVisible = !this->m_cursorVisible;
	if (this->m_cursorVisible) {
		// Cursor is Visible
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else {
		// Cursor is Hidden
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	// Log to Console
	std::cout << "[Window] Cursor is " << (this->m_cursorVisible ? "VISIBILE" : "HIDDEN") << std::endl;
}
