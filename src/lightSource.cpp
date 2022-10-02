#include "lightSource.h"


LightSource::LightSource(
	glm::vec3 position,
	glm::vec3 ambientColor,
	glm::vec3 diffusionColor,
	glm::vec3 specularColor
)
{
	lightPosition = position;
	lightAmbient = ambientColor;
	lightDiffusion = diffusionColor;
	lightSpecular = specularColor;
}


glm::vec3 LightSource::GetLightPosition()
{
	return lightPosition;
}


glm::vec3 LightSource::GetLightAmbient()
{
	return lightAmbient;
}


glm::vec3 LightSource::GetLightDiffusion()
{
	return lightDiffusion;
}


glm::vec3 LightSource::GetLightSpecular()
{
	return lightSpecular;
}