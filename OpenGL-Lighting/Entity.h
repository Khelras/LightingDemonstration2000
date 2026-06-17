/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Entity.h
 Description :   Declares the Entity Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once

#include "Mesh.h"
#include "Material.h"
#include "CameraFree.h"

class Entity {
private:
	// -- Entity Rendering Properties -- //
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Material> m_material;
	// -- //

	// -- Entity Transform Properties -- // 
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="mesh">Shared pointer to the mesh.</param>
	/// <param name="material">Shared pointer to the material.</param>
	Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Entity();

	//==================================================
	// PRIMARY ENTITY METHODS
	//==================================================

	/// <summary>
	///		Draw the entity into the world.
	/// </summary>
	/// 
	/// <param name="camera">Reference to the camera class.</param>
	void draw(CameraFree& camera) const;

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
	///		Material for the 3D object.
	/// </returns>
	Material* getMaterial() const;

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

