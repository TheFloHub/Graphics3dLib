#include "Shader.h"
#include <glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <streambuf>

// all global shader parameters
std::map<std::string, int> G3d::Shader::GlobalIntParameters;
std::map<std::string, float> G3d::Shader::GlobalFloatParameters;
std::map<std::string, glm::vec3> G3d::Shader::GlobalFloatVec3Parameters;
std::map<std::string, glm::mat3> G3d::Shader::GlobalMat3Parameters;
std::map<std::string, glm::mat4> G3d::Shader::GlobalMat4Parameters;

// global getters and setters
int G3d::Shader::getGlobalInt(std::string const& name)
{
	return GlobalIntParameters[name];
}

void G3d::Shader::setGlobalInt(std::string const& name, int value)
{
	GlobalIntParameters[name] = value;
}

float G3d::Shader::getGlobalFloat(std::string const& name)
{
	return GlobalFloatParameters[name];
}

void G3d::Shader::setGlobalFloat(std::string const& name, float value)
{
	GlobalFloatParameters[name] = value;
}

glm::vec3 const& G3d::Shader::getGlobalFloatVec3(std::string const& name)
{
	return GlobalFloatVec3Parameters[name];
}

void G3d::Shader::setGlobalFloatVec3(std::string const& name, glm::vec3 const& value)
{
	GlobalFloatVec3Parameters[name] = value;
}

glm::mat3 const& G3d::Shader::getGlobalMat3(std::string const& name)
{
	return GlobalMat3Parameters[name];
}

void G3d::Shader::setGlobalMat3(std::string const& name, glm::mat3 const& value)
{
	GlobalMat3Parameters[name] = value;
}

glm::mat4 const& G3d::Shader::getGlobalMat4(std::string const& name)
{
	return GlobalMat4Parameters[name];
}

void G3d::Shader::setGlobalMat4(std::string const& name, glm::mat4 const& value)
{
	GlobalMat4Parameters[name] = value;
}

// shader class
G3d::Shader::Shader(
	std::string const& vertexShaderCode,
	std::string const& fragmentShaderCode) : 
mShaderProgram(0)
{
	GLuint vertexShaderHandle = createShaderComponent(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShaderHandle = createShaderComponent(GL_FRAGMENT_SHADER, fragmentShaderCode);

	// link components to a shader program
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, vertexShaderHandle);
	glAttachShader(mShaderProgram, fragmentShaderHandle);
	glLinkProgram(mShaderProgram);

	// print linking errors if any
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShaderHandle);
	glDeleteShader(fragmentShaderHandle);
}



G3d::Shader::~Shader()
{
	if (mShaderProgram != 0)
		glDeleteShader(mShaderProgram);
}


GLuint G3d::Shader::createShaderComponent(GLuint const shaderType, std::string const& shaderCode) const
{
	GLuint shaderHandle = 0;
	GLchar const* pShaderCode = shaderCode.c_str();

	// compile shader
	shaderHandle = glCreateShader(shaderType);
	glShaderSource(shaderHandle, 1, &pShaderCode, NULL);
	glCompileShader(shaderHandle);

	// print compile errors if any
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shaderHandle;
}

void G3d::Shader::use() const
{
	glUseProgram(mShaderProgram); 
}

GLint G3d::Shader::getUniformLocation(std::string const & name) const
{
	return glGetUniformLocation(mShaderProgram, name.c_str());
}

GLuint G3d::Shader::getHandle() const
{
	return mShaderProgram;
}

