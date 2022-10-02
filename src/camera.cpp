#include "camera.h"

#include <cmath>


Camera::Camera(glm::vec3 position, glm::vec3 upVector, float viewRatio, float fov, float sensetivity)
{
    positionVector = position;
    worldUpVector = upVector;
    mouseSensetivity = sensetivity;
    movementSpeed = 3.0f;
    FOV = fov;
    aspectRatio = viewRatio;
    yaw = 90.0f;
    pitch = 0.0f;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(positionVector, positionVector + frontVector, upVector);
}

float Camera::GetFOV()
{
    return FOV;
}


glm::vec3 Camera::GetPosition()
{
    return positionVector;
}


float Camera::GetAspectRatio()
{
    return aspectRatio;
}


void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVector = glm::normalize(front);
    
    rightVector = glm::cross(frontVector, worldUpVector);
    rightVector = glm::normalize(rightVector);

    upVector = glm::cross(rightVector, frontVector);
    upVector = glm::normalize(upVector);
}


void Camera::RotateCameraByMouse(float xOffset, float yOffset)
{
    yaw += xOffset * mouseSensetivity;
    pitch += yOffset * mouseSensetivity;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    UpdateCameraVectors();
}


void Camera::MoveCamera(CAMERA_MOVEMENT direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD) {
        positionVector += frontVector * velocity;
    }
    if (direction == BACKWARD) {
        positionVector -= frontVector * velocity;
    }
    if (direction == RIGHT) {
        positionVector += rightVector * velocity;
    }
    if (direction == LEFT) {
        positionVector -= rightVector * velocity;
    }
}