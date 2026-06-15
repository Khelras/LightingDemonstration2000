/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Shader.h
 Description :   Declares the Shader Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>

#include "ShaderLoader.h"

/// <summary>
///		Wraps the OpenGL shader program and provide utility functions to easily set uniform variables.
/// </summary>
class Shader {
private:
	// -- Shader Properties -- //
	GLuint m_programID;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================
	
	/// <summary>
	///		Constructor.
	/// </summary>
	/// 
	/// <param name="vertexPath">File path to vertex shader.</param>
	/// <param name="fragmentPath">File path to fragment shader.</param>
	Shader(const char* vertexPath, const char* fragmentPath);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Shader();

	//==================================================
	// PRIMARY SHADER METHODS
	//==================================================

	/// <summary>
	///		Bind to the shader program.
	/// </summary>
	void use();

	/// <summary>
	///		Sets an integer uniform.
	/// </summary>
	/// 
	/// <param name="name">Name of the uniform.</param>
	/// <param name="value">Value to set.</param>
	void setInt(const std::string& name, int value) const;

	/// <summary>
	///		Sets a floating-point uniform.
	/// </summary>
	/// 
	/// <param name="name">Name of the uniform.</param>
	/// <param name="value">Value to set.</param>
	void setFloat(const std::string& name, float value) const;

	/// <summary>
	///		Sets a 3D vector uniform.
	/// </summary>
	/// 
	/// <param name="name">Name of the uniform.</param>
	/// <param name="value">Value to set.</param>
	void setVec3(const std::string& name, const glm::vec3& value) const;

	/// <summary>
	///		Sets a 4x4 matrix uniform.
	/// </summary>
	/// 
	/// <param name="name">Name of the uniform.</param>
	/// <param name="value">Value to set.</param>
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

