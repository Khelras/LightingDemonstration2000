/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Scene.h
 Description :   Declares the Scene Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <vector>

#include "Entity.h"

/// <summary>
///     Scene class representing a self-contained state of the application.
///     A Scene groups together elements such as objects, UI, logic,
///		and assets relevant to that state of the application.
/// </summary>
class Scene {
private:
	// -- Scene Properties -- //
	std::vector<std::unique_ptr<Entity>> m_entities;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor.
	/// </summary>
	Scene();

	/// <summary>
	///		Default Destructor.
	/// </summary>
	~Scene();

	//==================================================
	// PRIMARY SCENE METHODS
	//==================================================

	/// <summary>
	///		Initialise the all the objects in the Scene.
	/// </summary>
	void initialise();

	/// <summary>
	///		Initialise the UI in the Scnee.
	/// </summary>
	/// 
	/// <param name="windowWidth">Width of the window.</param>
	/// <param name="windowHeight">Height of the window.</param>
	void initialiseUI(float windowWidth, float windowHeight);

	/// <summary>
	///		Get all the entities in the scene.
	/// </summary>
	/// 
	/// <returns>
	///		List of the entities in the scene as a vector.
	/// </returns>
	std::vector<std::unique_ptr<Entity>>& getEntities();

	/// <summary>
	///		Update the Scene.
	/// </summary>
	/// 
	/// <param name="deltaTime">Delta Time as a float.</param>
	void update(float deltaTime);

	/// <summary>
	///		Render all the entities in the Scene.
	/// </summary>
	/// 
	/// <param name="camera">Reference to the Camera.</param>
	void render(CameraFree& camera);
};
