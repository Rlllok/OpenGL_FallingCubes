#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera
{
private:
	
	float yaw;
	float pitch;
	float FOV;
	float aspectRatio;
	float mouseSensetivity;
	float movementSpeed;
	glm::vec3 positionVector;
	glm::vec3 worldUpVector;
	glm::vec3 frontVector;
	glm::vec3 rightVector;
	glm::vec3 upVector;

	void UpdateCameraVectors();

public:

	enum CAMERA_MOVEMENT {
		FORWARD,
		BACKWARD,
		RIGHT,
		LEFT
	};

	Camera(
		glm::vec3 position,
		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f),
		float viewRatio = 16.0 / 9.0,
		float fov = 45.0f,
		float sensetivity = 0.1f
	);

	glm::mat4 GetViewMatrix();
	float GetFOV();
	glm::vec3 GetPosition();
	float GetAspectRatio();
	void RotateCameraByMouse(float xOffset, float yOffset);
	void MoveCamera(CAMERA_MOVEMENT direction, float deltaTime);
};

