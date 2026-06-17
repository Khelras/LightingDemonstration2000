/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Shader.cpp
 Description :   Defines the Shader Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// Create the Shader Program
	this->m_programID = ShaderLoader::CreateProgram(vertexPath, fragmentPath);
}

Shader::~Shader() {
}

void Shader::use() {
	// Bind and use the Shader Program
	glUseProgram(this->m_programID);
}

const GLuint& Shader::getProgramID() const {
	return this->m_programID;
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(this->m_programID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(this->m_programID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(this->m_programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(this->m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
