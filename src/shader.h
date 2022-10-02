#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>


class Shader
{
private:
	
	unsigned int ID;

	enum ERRORS_TYPES {
		SHADER_COMPILE,
		SHADER_LINK
	};

public:

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Use();
	unsigned int GetID();
	void CheckErrors(unsigned int shader, ERRORS_TYPES type);
	void SetUniformFloat(const char* name, float value);
	void SetUniformInt(const char* name, int value);
	void SetUnifromMat3(const char* name, glm::mat3 matrix);
	void SetUniformMat4(const char* name, glm::mat4 matrix);
	void SetUniformVec3(const char* name, float x, float y, float z);
	void SetUniformVec3(const char* name, glm::vec3 vector);
	unsigned int loadTexture(char const* path);
};

