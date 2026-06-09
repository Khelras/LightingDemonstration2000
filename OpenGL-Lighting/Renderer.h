/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Renderer.h
 Description :   Declares the Renderer Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include "Scene.h"
#include "Camera.h"

/// <summary>
///		Handles the rendering of the world objects to the screen.
/// </summary>
class Renderer {
private:
	// -- Renderer Properties -- //
	GLuint m_program;
	bool m_wireframeActive;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	Renderer();

	/// <summary>
	///		Destructor.
	/// </summary>
	~Renderer();

	//==================================================
	// PRIMARY RENDERER METHODS
	//==================================================

	/// <summary>
	///		Initialise the Renderer.
	/// </summary>
	/// 
	/// <param name="vertPath">File path to the vertex shader file.</param>
	/// <param name="fragPath">File path to the fragment shader file.</param>
	void initialise(const std::string& vertPath, const std::string& fragPath);

	/// <summary>
	///		Render a given scene and a given camera.
	/// </summary>
	/// 
	/// <param name="scene">Reference to the scene to render.</param>
	/// <param name="camera">Reference to the camera for rendering.</param>
	void render(const Scene& scene, Camera& camera);

	/// <summary>
	///		Toggle the wireframe rendering of the 3D model.
	/// </summary>
	void toggleWireframe();
};

