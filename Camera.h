#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"


class Camera {
private:
	glm::vec3 Front;
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Right;
	glm::vec3 Up;

	double yaw = -90.0f;
	double pitch = 0.0f;
	GLfloat sensitivity = 0.1f;
	GLfloat speed = 2.5f;

	double deltaFrame = 0.0f;
	double lastFrame = 0.0f;

public:
	glm::vec3 Position;
	GLfloat zoom = 45.0f;

	Camera(glm::vec3 cameraposition);

	void initMouse(GLFWwindow* window);
	glm::mat4 getViewMatrix();
	void processWindowKeys(GLFWwindow* window);
	void getDeltaTimeStamp();

	void processOffsetMovement(double offsetX, double offsetY);
	void processOffsetScroll(double offsety);

private:

	void updateCameraVectors();

};