/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   ShaderLoader.h
 Description :   A ShaderLoader Class that was provided in GD1P04_26022 :D
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#include "ShaderLoader.h" 
#include <fstream>

std::map<std::string, GLuint> ShaderLoader::m_shaderIDs;
std::map<std::string, GLuint> ShaderLoader::m_programs;

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

GLuint ShaderLoader::CreateShader(GLenum _shaderType, const char* _shaderName)
{
	// Read the shader files and save the source code as strings
	std::string shaderSourceCode = ReadShaderFile(_shaderName);

	// Create the shader ID and create pointers for source code string and length
	GLuint shaderID = glCreateShader(_shaderType);
	const char* SHADER_CODE_PTR = shaderSourceCode.c_str();
	const int SHADER_CODE_SIZE = static_cast<int>(shaderSourceCode.size());

	// Populate the Shader Object (ID) and compile
	glShaderSource(shaderID, 1, &SHADER_CODE_PTR, &SHADER_CODE_SIZE);
	glCompileShader(shaderID);

	// Check for errors
	int compile_result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		PrintErrorDetails(true, shaderID, _shaderName);
		return 0;
	}
	return shaderID;
}

std::string ShaderLoader::ReadShaderFile(const char* _filename)
{
	// Open the file for reading
	std::ifstream file(_filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << _filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg); // Set the position of the next character to be read back to the beginning
	file.read(&shaderCode[0], shaderCode.size()); // Extract the contents of the file and store in the string variable
	file.close();

	// Return the Shader Code
	return shaderCode;
}

void ShaderLoader::PrintErrorDetails(bool _isShader, GLuint id, const char* _name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(_isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(_isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((_isShader == true) ? "shader" : "program") << ": " << _name << std::endl;
	std::cout << &log[0] << std::endl;
}

GLuint ShaderLoader::CreateProgram(const char* _vertexShaderFilename, const char* _fragmentShaderFilename)
{
	// Convert to non-literal Strings for Map Keys
	std::string v = _vertexShaderFilename;
	std::string f = _fragmentShaderFilename;
	std::string key = "v: " + v + " f: " + f; // Key for Program

	// Shader IDs and Program
	GLuint vertexShaderID, fragmentShaderID, program = 0;

	// Check for existing Vertex Shader ID from File Path
	if (m_shaderIDs.find(v) != m_shaderIDs.end()) {
		// Use existing Vertex Shader ID
		vertexShaderID = m_shaderIDs[v];
	}
	else {
		// Create Vertex Shader ID and store it into Shader ID Map
		vertexShaderID = CreateShader(GL_VERTEX_SHADER, _vertexShaderFilename);
		m_shaderIDs[v] = vertexShaderID;
	}

	// Check for existing Fragment Shader ID from File Path
	if (m_shaderIDs.find(f) != m_shaderIDs.end()) {
		// Use existing Fragment Shader ID
		fragmentShaderID = m_shaderIDs[f];
	}
	else {
		// Create Fragment Shader ID and store it into Shader ID Map
		fragmentShaderID = CreateShader(GL_FRAGMENT_SHADER, _fragmentShaderFilename);
		m_shaderIDs[f] = fragmentShaderID;
	}

	// Check if Program exists
	if (m_programs.find(key) != m_programs.end()) {
		// Use existing Program
		program = m_programs[key];
	}
	else {
		// Create the program handle, attach the shaders and link it
		program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);
		glLinkProgram(program);

		// Check for link errors
		int link_result = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);
		if (link_result == GL_FALSE) {
			std::string programName = _vertexShaderFilename + *_fragmentShaderFilename;
			PrintErrorDetails(false, program, programName.c_str());
			return 0;
		}

		// Detach Shaders
		glDetachShader(program, vertexShaderID);
		glDetachShader(program, fragmentShaderID);

		// Store into Map
		m_programs[key] = program;
	}

	// Return the Program
	return program;
}