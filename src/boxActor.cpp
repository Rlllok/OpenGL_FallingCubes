#include "boxActor.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "collisionBox.h"
#include "collisionBody.h"
#include "world.h"
#include <iostream>


BoxActor::BoxActor(World* world, Material* material, btVector3 position, btQuaternion rotation, float boxMass)
{
	existenceWorld = world;
	originPosition = position;
	originOrientation = rotation;
	mass = boxMass;
	boxMaterial = material;
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1,&VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	collision = new CollisionBox(originPosition, originOrientation, btVector3(0.5f, 0.5f, 0.5f), mass);
}


BoxActor::~BoxActor()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	delete collision;
}


void BoxActor::Tick(float deltaTime)
{
	lifeTime += deltaTime;
	if (lifeTime >= 5.0f) {
		existenceWorld->RemoveActor(this);
		delete this;
	}
}


void BoxActor::Display()
{
	Shader* shader = boxMaterial->GetShader();
	shader->SetUniformVec3("viewPos", existenceWorld->GetCamera()->GetPosition());

	boxMaterial->SetTexture();

	btTransform transformMatrix;
	collision->GetRigidBody()->getMotionState()->getWorldTransform(transformMatrix);
	float mat[16];
	transformMatrix.getOpenGLMatrix(mat);

	glm::mat4 view = glm::mat4(1.0f);
	view = existenceWorld->GetCamera()->GetViewMatrix();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(existenceWorld->GetCamera()->GetFOV()), existenceWorld->GetCamera()->GetAspectRatio(), 0.1f, 100.0f);
	unsigned int mLoc = glGetUniformLocation(shader->GetID(), "model");
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, mat);
	shader->SetUniformMat4("view", view);
	shader->SetUniformMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}