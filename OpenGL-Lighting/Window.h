/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Window.h
 Description :   Declares the Window Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include "Renderer.h"

 /// <summary>
 ///	Window class that uses GLFW to initialize and create an OpenGL window.
 /// </summary>
class Window {
private:
	// -- Window Properties -- //
	GLFWwindow* m_window;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	bool m_cursorVisible;

	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Scene> m_scene;
	std::unique_ptr<Renderer> m_renderer;
	// -- //

	// -- Time -- //
	float m_currentTime;
	float m_previousTime;
	float m_deltaTime;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructs a Window with the specified width and height.
	/// </summary>
	/// 
	/// <param name="width">Width of the Window in pixels</param>
	/// <param name="height">Height of the Window in pixels</param>
	Window(unsigned int width, unsigned int height);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Window();

	//==================================================
	// PRIMARY WINDOW METHODS
	//==================================================

	/// <summary>
	///		Initializes GLFW and creates a GLFW Window.
	/// </summary>
	/// 
	/// <param name="major">Major version of OpenGL e.g. 4.x.</param>
	/// <param name="minor">Minor version of OpenGL e.g. x.3.</param>
	/// 
	/// <returns>
	///		True if initialization succeeds and GLFW Window was successfully created.
	///		False if there was an error during the initialization process of creating a GLFW Window.
	/// </returns>
	bool initialize(int major = 4, int minor = 3);

	/// <summary>
	///		Processes the overall Window logic.
	/// </summary>
	/// 
	/// <returns>
	///		True if the window is still running and the main loop should continue.
	///		False if the window has been closed.
	/// </returns>
	bool process();

	/// <summary>
	///		Polls for events such as window events or input events.
	/// </summary>
	void pollEvents();

	/// <summary>
	///		Updates all active objects and logic.
	///		Primarily handles CPU-side simulation and state updates.
	/// </summary>
	void update();

	/// <summary>
	///		Renders all visible objects.
	///		Primarily handles GPU-side rendering operations; including drawing to the
	///		back buffer and swapping buffers to present the final frame.
	/// </summary>
	void render();

private:
	//==================================================
	// HELPER METHODS
	//==================================================

	/// <summary>
	///		Handle and process the movement inputs.
	/// </summary>
	void handleMovement();

	/// <summary>
	///		Toggle the cursor visibility.
	/// </summary>
	void toggleCursorVisibility();
};

