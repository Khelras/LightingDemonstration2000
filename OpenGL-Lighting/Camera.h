/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Camera.h
 Description :   Declares the Camera Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

 /// <summary>
 ///	Camera class that holds the view and projection information and display it to the Window.
 /// </summary>
class Camera {
protected:
	// -- Window Properties -- //
	float m_windowWidth;
	float m_windowHeight;
	// -- //

	// -- Camera View Properties -- //
	glm::vec3 m_position;
	glm::vec3 m_lookDirection;
	glm::vec3 m_upDireciton;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructs a Camera.
	/// </summary>
	/// 
	/// <param name="windowWidth">Width of the Window in pixels</param>
	/// <param name="windowHeight">Height of the Window in pixels</param>
	Camera(float windowWidth, float windowHeight);

	/// <summary>
	///		Destructor.
	/// </summary>
	virtual ~Camera();

	//==================================================
	// PRIMARY CAMERA METHODS
	//==================================================

	/// <summary>
	///		Gets the Camera view based on the current Camera properties.
	/// </summary>
	/// 
	/// <returns>
	///		4x4 matrix of the Camera view.
	/// </returns>
	virtual glm::mat4 getCameraView();

	/// <summary>
	///		Gets an orthographic projection matrix of the Camera.
	/// </summary>
	/// 
	/// <returns>
	///		4x4 matrix of the orthographic projection of the Camera.
	/// </returns>
	virtual glm::mat4 getCameraOrtho();

	/// <summary>
	///		Gets a perspective projection matrix of the Camera.
	/// </summary>
	/// 
	/// <param name="fov">Field of View (as degrees). Defaulted to 45 degrees.</param>
	/// 
	/// <returns>
	///		4x4 matrix of the perspective projection of the Camera.
	/// </returns>
	virtual glm::mat4 getCameraPerspec(float fov = 45.0f);

	//==================================================
	// GETTER METHODS
	//==================================================

	/// <summary>
	///		Get the world position of the camera.
	/// </summary>
	/// 
	/// <returns>
	///		3D position vector.
	/// </returns>
	glm::vec3 getCameraPosition() const;

	//==================================================
	// SETTER METHODS
	//==================================================

	/// <summary>
	///		Sets the position of the Camera.
	/// </summary>
	/// 
	/// <param name="position">3D vector (x, y, z) as world coordinates.</param>
	void setCameraPosition(glm::vec3 position);

	/// <summary>
	///		Sets the direction vector of which the Camera is looking towards.
	/// </summary>
	/// 
	/// <param name="direction">3D vector (x, y, z).</param>
	void setCameraLookDireciton(glm::vec3 direction);

	/// <summary>
	///		Sets the upwards direction vector of the Camera.
	/// </summary>
	/// 
	/// <param name="direction">3D vector (x, y, z) representing the up direction of the Camera.</param>
	void setCameraUpDirection(glm::vec3 direction);
};