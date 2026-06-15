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
#include <memory>

#include "Mesh.h"
#include "Texture2D.h"

/// <summary>
///     Scene class representing a self-contained state of the application.
///     A Scene groups together elements such as objects, UI, logic,
///		and assets relevant to that state of the application.
/// </summary>
class Scene {
private:
	// -- Single 3D Object Properties -- //
	std::unique_ptr<Mesh> m_model;
	std::unique_ptr<Texture2D> m_texture;
	
	const float m_moveSpeed = 10.0f;
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f);
	// -- //

	// -- UI Properties -- //
	
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
	/// 
	/// <param name="modelPath">File path to the '.obj' file of the model.</param>
	void initialise(const std::string& modelPath);

	/// <summary>
	///		Initialise the UI in the Scnee.
	/// </summary>
	/// 
	/// <param name="windowWidth">Width of the window.</param>
	/// <param name="windowHeight">Height of the window.</param>
	void initialiseUI(float windowWidth, float windowHeight);

	/// <summary>
	///		Update the Scene.
	/// </summary>
	/// 
	/// <param name="deltaTime">Delta Time as a float.</param>
	void update(float deltaTime);

	/// <summary>
	///		Move the 3D model.
	/// </summary>
	/// 
	/// <param name="delta">3D delta movement vector.</param>
	void moveObject(glm::vec3 delta);

	//==================================================
	// GETTER METHODS
	//==================================================

	/// <summary>
	///		Get the Model Mesh of the 3D object.
	/// </summary>
	/// 
	/// <returns>
	///		Model Mesh of the 3D object.
	/// </returns>
	Mesh* getModel() const;

	/// <summary>
	///		Get the texture for the 3D object.
	/// </summary>
	/// 
	/// <returns>
	///		Texture for the 3D object.
	/// </returns>
	Texture2D* getTexture() const;
	
	/// <summary>
	///		Get the world position of the 3D model.
	/// </summary>
	/// 
	/// <returns>
	///		3D position vector of the 3D model.
	/// </returns>
	glm::vec3 getPosition() const;

	/// <summary>
	///		Get the rotation of the 3D model.
	/// </summary>
	/// 
	/// <returns>
	///		3D rotation vector of the 3D model.
	/// </returns>
	glm::vec3 getRotation() const;

	/// <summary>
	///		Get the scale of the 3D model.
	/// </summary>
	/// 
	/// <returns>
	///		3D scale vector of the 3D model.
	/// </returns>
	glm::vec3 getScale() const;

	/// <summary>
	///		Calculates and returns a model matrix based on the 3D object's transformation properties.
	///		First converts and construct translation, rotation, and scale matrices from the sprite transformation properties.
	///		These matrices are required to caculate and create the model matrix.
	///		The model matrix is calculated by multiplying the translation, rotation, and scale matrices together in that order.
	///		This will apply the transformations in this order: scale -> rotate -> translate.
	/// </summary>
	/// 
	/// <returns>
	///		4x4 model matrix which holds the position, rotation, and scale of the Sprite.
	/// </returns>
	glm::mat4 getModelMatrix() const;

	//==================================================
	// SETTER METHODS
	//==================================================

	/// <summary>
	///		Set the world position of the 3D model.
	/// </summary>
	/// <param name="position">3D position vector.</param>
	void setPosition(glm::vec3 position);

	/// <summary>
	///		Set the rotation of the 3D model.
	/// </summary>
	/// <param name="position">3D rotation vector.</param>
	void setRotation(glm::vec3 rotation);

	/// <summary>
	///		Set the scale of the 3D model.
	/// </summary>
	/// <param name="position">3D scale vector.</param>
	void setScale(glm::vec3 scale);
};
