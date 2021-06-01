#include"Camera.h"

Camera::Camera(glm::vec3 cameraposition) : Position(cameraposition)
{
	updateCameraVectors();
}

void Camera::initMouse(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processWindowKeys(GLFWwindow* window) {
	GLfloat velocity = speed * deltaFrame;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += Front * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= Front * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += Right * velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= Right * velocity;

	//Position.y = 0.0f;

}

void Camera::getDeltaTimeStamp() {
	double currentFrame = glfwGetTime();
	deltaFrame = currentFrame - lastFrame;
	lastFrame = currentFrame;
}



void Camera::processOffsetMovement(double offsetX,double offsetY) {
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));	//cospitch * cosyaw;
	front.y = sin(glm::radians(pitch));								//sinpitch;
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));	//cospitch * sinyaw
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right,Front));
}

void Camera::processOffsetScroll( double yoffset) {
	if (zoom < 1.0f) zoom = 1.0f;
	if (zoom > 45.0f) zoom = 45.0f;

	zoom -= (GLfloat)yoffset;
}