#include "planeActor.h"
#include "world.h"
#include "collisionBox.h"
#include "glad/glad.h"


PlaneActor::PlaneActor(World* world, Material* material, btVector3 position, float height, float width)
{
	existenceWorld = world;
	originPosition = position;
	this->height = height;
	this->width = width;
	this->material = material;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	collision = new CollisionBox(originPosition, btQuaternion(0.0f, 0.0f, 0.0f), btVector3(width / 2.0, 0.0f, height / 2.0), 0.0f);
}


void PlaneActor::Display()
{
	Shader* shader = material->GetShader();
	if (shader != nullptr) {
		shader->SetUniformVec3("viewPos", existenceWorld->GetCamera()->GetPosition());

		material->SetTexture();

		btTransform transformMatrix;
		collision->GetRigidBody()->getMotionState()->getWorldTransform(transformMatrix);
		float mat[16];
		transformMatrix.getOpenGLMatrix(mat);
		mat[0] *= height;
		mat[10] *= width;

		glm::mat4 view = glm::mat4(1.0f);
		view = existenceWorld->GetCamera()->GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(existenceWorld->GetCamera()->GetFOV()), existenceWorld->GetCamera()->GetAspectRatio(), 0.1f, 100.0f);
		unsigned int mLoc = glGetUniformLocation(shader->GetID(), "model");
		glUniformMatrix4fv(mLoc, 1, GL_FALSE, mat);
		shader->SetUniformMat4("view", view);
		shader->SetUniformMat4("projection", projection);
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}