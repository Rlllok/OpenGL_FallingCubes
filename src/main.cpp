#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>
#include <vector>
#include "boxActor.h"
#include "planeActor.h"
#include "camera.h"
#include "stb_image.h"
#include "world.h"
#include "material.h"
#include <time.h>
#include <random>


void processInput(GLFWwindow* window, World* world, float deltaTime);
void CreateBox(World* world, Material* material, btVector3 position, btQuaternion rotation, float mass);
void fpsCounterInTitle(GLFWwindow* window, const char* title, float deltaTime);


int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 720;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Home Task", NULL, NULL);

	if (!window) {
		std::cout << "Cannot create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Cannot initialize GLAD." << std::endl;
		glfwTerminate();
		return -1;
	}

	Camera* camera = new Camera(glm::vec3(0.0f, 3.0f, -10.0f));
	LightSource* lightSource = new LightSource(
		glm::vec3(2.0f, 3.0f, -4.0f),
		glm::vec3(0.4f),
		glm::vec3(0.7f),
		glm::vec3(1.0f)
	);
	World* world = new World(camera, lightSource);

	Material material(
		world,
		".\\data\\plane_diff.jpg",
		".\\data\\plane_spec.jpg",
		32.0f
	);

	PlaneActor* plane = new PlaneActor(world, &material, btVector3(0.0f, 0.0f, 0.0f), 5.0f, 5.0f);
	world->AddActor(plane);
	glm::vec3 Light = world->GetLightSource()->GetLightPosition();

	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);
	srand(time(NULL));

	float lastTime = 0;
	float lastXPos;
	float lastYPos;
	unsigned int frameCounter = 0;
	bool isFirstMouseInput = true;
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		fpsCounterInTitle(window, "OpenGL Home Task", deltaTime);

		double xPosInput;
		double yPosInput;
		glfwGetCursorPos(window, &xPosInput, &yPosInput);

		float xPos = static_cast<float>(xPosInput);
		float yPos = static_cast<float>(yPosInput);

		if (isFirstMouseInput) {
			lastXPos = xPos;
			lastYPos = yPos;
			isFirstMouseInput = false;
		}

		float xOffset = xPos - lastXPos;
		float yOffset = lastYPos - yPos;

		lastXPos = xPos;
		lastYPos = yPos;

		world->GetCamera()->RotateCameraByMouse(xOffset, yOffset);

		processInput(window, world, deltaTime);
		world->Tick(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}


void processInput(GLFWwindow* window, World* world, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		world->GetCamera()->MoveCamera(Camera::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		world->GetCamera()->MoveCamera(Camera::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		world->GetCamera()->MoveCamera(Camera::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		world->GetCamera()->MoveCamera(Camera::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		world->GetCamera()->RotateCameraByMouse(0.0f, -0.2f);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		world->GetCamera()->RotateCameraByMouse(0.0f, 0.2f);
	}

	static bool MouseIsPressed = false;
	static Material boxMaterial(
		world,
		".\\data\\brick_wall_diff.tga",
		".\\data\\brick_wall_spec.tga",
		32.0f
	);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		if (MouseIsPressed == false) {
			CreateBox(world, &boxMaterial, btVector3(0.0f, 10.0f, 0.0f), btQuaternion(rand() % 360, rand() % 360, rand() % 360), 0.1f);
		}
		MouseIsPressed = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
		MouseIsPressed = false;
	}
}


void CreateBox(World* world, Material* material, btVector3 position, btQuaternion rotation, float mass)
{
	BoxActor* box1 = new BoxActor(world, material, position, rotation, mass);
	world->AddActor(box1);
}


void fpsCounterInTitle(GLFWwindow* window, const char* title, float deltaTime)
{
	static float time = 0;
	static unsigned int nFrames = 0;
	time += deltaTime;
	nFrames++;
	if (time >= 1.0f) {
		std::string msPerFrame = std::to_string(1000.0 / nFrames);
		std::string FPS = std::to_string(nFrames / time);
		std::string result = std::string(title) + " " + msPerFrame + " ms" + " | " + FPS + " FPS";
		glfwSetWindowTitle(window, result.c_str());
		nFrames = 0;
		time = 0.0f;
	}
}