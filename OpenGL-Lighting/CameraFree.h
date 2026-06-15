/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   CameraFree.h
 Description :   Declares the CameraFree Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include "Camera.h"

/// <summary>
///		Free Camera class that inherits from the Camera class and extends the
///		functionality to allow the User to move the Camera freely in the 3D space.
/// </summary>
class CameraFree : public Camera {
private:
	// -- Free Camera Properties -- //
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_yaw;
	float m_pitch;
	// -- //

	// -- Cursor Movement Properties -- //
	bool m_firstMouse;
	float m_cursorLastX;
	float m_cursorLastY;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="windowWidth">Width of the Window in pixels</param>
	/// <param name="windowHeight">Height of the Window in pixels</param>
	CameraFree(float windowWidth, float windowHeight);

	/// <summary>
	///		Destructor.
	/// </summary>
	~CameraFree();

	//==================================================
	// PRIMARY CAMERA FREE METHODS
	//==================================================

	/// <summary>
	///		Handle the Free Camera Movement.
	/// </summary>
	/// 
	/// <param name="deltaTime"><Delta Time as a Float./param>
	void handleFreeCameraMovement(float deltaTime);

	//==================================================
	// SETTER METHODS
	//==================================================

	/// <summary>
	///		Set the Movement Speed of the Free Camera.
	/// </summary>
	/// 
	/// <param name="speed">Movement Speed.</param>
	void setMovementSpeed(float speed);
	
	/// <summary>
	///		Set the Mouse Sensitivity of the Free Camera.
	/// </summary>
	/// 
	/// <param name="sensitivity">Mouse Sensitivity.</param>
	void setMouseSensitivity(float sensitivity);

private:
};

