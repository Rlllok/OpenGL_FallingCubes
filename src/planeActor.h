#pragma once

#include "actor.h"
#include "world.h"
#include "shader.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "material.h"


class PlaneActor : public Actor
{
private:

	World* existenceWorld;
	// Plane Properties;
	float height;
	float width;
	Material* material;
	// OpenGL Variables;
	unsigned int VBO, VAO;

	float vertices[6 * 8] = {
		// positions          // normals           // texture coords
		 0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

public:

	PlaneActor(World* world, Material* material, btVector3 position, float height, float width);
	virtual void Display() override;
	virtual void Tick(float deltaTime) { };

};