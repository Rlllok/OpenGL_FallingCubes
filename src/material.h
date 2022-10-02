#pragma once 

#include "shader.h"
#include "world.h"
#include "glm/glm.hpp"


class Material
{
private:

	Shader* shader;
	World* world;
	unsigned int diffuseMap;
	unsigned int specularMap;
	float shininess;

public:
	
	Material(
		World* world,
		const char* diffuseMapPath,
		const char* specularMapPath,
		float shininess
	);
	~Material();

	void UseShader();
	void SetTexture();
	Shader* GetShader();
};