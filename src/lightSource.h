#pragma once

#include "glm/glm.hpp"

class LightSource
{
private:
	glm::vec3 lightPosition;
	glm::vec3 lightAmbient;
	glm::vec3 lightDiffusion;
	glm::vec3 lightSpecular;

public:

	LightSource(
		glm::vec3 position,
		glm::vec3 ambientColor,
		glm::vec3 diffusionColor,
		glm::vec3 specularColor
	);
	glm::vec3 GetLightPosition();
	glm::vec3 GetLightAmbient();
	glm::vec3 GetLightDiffusion();
	glm::vec3 GetLightSpecular();
};