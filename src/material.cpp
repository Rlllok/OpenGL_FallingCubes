#include "material.h"
#include "glad/glad.h"
#include "lightSource.h"


Material::Material(
	World* world,
	const char* diffuseMapPath,
	const char* specularMapPath,
	float shininess
)
{
	this->world = world;
	shader = new Shader(".\\shader\\lightingShader.vs", ".\\shader\\lightingShader.fs");

	diffuseMap = shader->loadTexture(diffuseMapPath);
	specularMap = shader->loadTexture(specularMapPath);

	this->shininess = shininess;
	LightSource* lightSource = world->GetLightSource();

	shader->Use();
	shader->SetUniformInt("material.diffuse", 0);
	shader->SetUniformInt("material.specular", 1);
	shader->SetUniformFloat("material.shininess", shininess);
	shader->SetUniformVec3("light.position", lightSource->GetLightPosition());
	shader->SetUniformVec3("light.ambient", lightSource->GetLightAmbient());
	shader->SetUniformVec3("light.diffuse", lightSource->GetLightDiffusion());
	shader->SetUniformVec3("light.specular", lightSource->GetLightSpecular());
}


Material::~Material()
{
	delete shader;
}


void Material::UseShader()
{
	shader->Use();
}


void Material::SetTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);
}


Shader* Material::GetShader()
{
	return shader;
}