/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   ShaderLoader.h
 Description :   A ShaderLoader Class that was provided by GD1P04_26022 :D
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <map>

class ShaderLoader {
private:
	// Private Member Variables
	static std::map<std::string, GLuint> m_shaderIDs;
	static std::map<std::string, GLuint> m_programs;

	// Private Constructor and Destructor
	ShaderLoader(void);
	~ShaderLoader(void);

	static GLuint CreateShader(GLenum _shaderType, const char* _shaderName);
	static std::string ReadShaderFile(const char* _filename);
	static void PrintErrorDetails(bool _isShader, GLuint id, const char* _name);

public:	
	static GLuint CreateProgram(const char* _vertexShaderFilename, const char* _fragmentShaderFilename);
};