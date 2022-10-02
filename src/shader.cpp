#include "shader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexShaderPath);
		std::stringstream vertexStream;
		vertexStream << vertexFile.rdbuf();
		vertexCode = vertexStream.str();
		vertexFile.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "SHADER FILE ERROR: FILE " << vertexShaderPath << "NOT READED. " << e.what() << std::endl;
	}

	try {
		fragmentFile.open(fragmentShaderPath);
		std::stringstream fragmentStream;
		fragmentStream << fragmentFile.rdbuf();
		fragmentCode = fragmentStream.str();
		fragmentFile.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "SHADER FILE ERROR: FILE " << fragmentShaderPath << "NOT READED. " << e.what() << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	unsigned int vertex;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckErrors(vertex, SHADER_COMPILE);

	const char* fShaderCode = fragmentCode.c_str();
	unsigned int fragment;
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckErrors(fragment, SHADER_COMPILE);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	CheckErrors(ID, SHADER_LINK);
}


void Shader::Use()
{
	glUseProgram(ID);
}


unsigned int Shader::GetID()
{
	return ID;
}


void Shader::CheckErrors(unsigned int shader, ERRORS_TYPES type)
{
	int success;
	char infoLog[1024];

	if (type == SHADER_COMPILE) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER COMPILE ERROR\n" << infoLog << std::endl << std::endl;
		}
	}

	if (type == SHADER_LINK) {
		glGetProgramiv (shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER LINK ERROR\n" << infoLog << std::endl << std::endl;
		}
	}
}


void Shader::SetUniformFloat(const char* name, float value)
{
	unsigned int location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cout << "Cannot find " << name << " in the shader." << std::endl;
		return;
	}
	glUniform1f(location, value);
}


void Shader::SetUniformInt(const char* name, int value)
{
	unsigned int location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cout << "Cannot find " << name << " in the shader." << std::endl;
		return;
	}
	glUniform1i(location, value);
}


void Shader::SetUnifromMat3(const char* name, glm::mat3 matrix)
{
	unsigned int location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cout << "Cannot find " << name << " in the shader." << std::endl;
		return;
	}
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::SetUniformMat4(const char* name, glm::mat4 matrix)
{
	unsigned int location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cout << "Cannot find " << name << " in the shader." << std::endl;
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::SetUniformVec3(const char* name, float x, float y, float z)
{
	unsigned int location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cout << "Cannot find " << name << " in the shader." << std::endl;
		return;
	}
	glUniform3f(location, x, y, z);
}


void Shader::SetUniformVec3(const char* name, glm::vec3 vector)
{
	unsigned int location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cout << "Cannot find " << name << " in the shader." << std::endl;
		return;
	}
	glUniform3f(location, vector.x, vector.y, vector.z);
}


unsigned int Shader::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}