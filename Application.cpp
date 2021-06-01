#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
//#include"imgui/imgui.h"
//#include"imgui/imgui_impl_glfw.h"
//#include"imgui/imgui_impl_opengl3.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include"Texture.h"
#include"Camera.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


using namespace std;

void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

Camera camera(glm::vec3(-5.0f,5.0f,10.0f));
bool firstMouse = false;
double lastX = SCREEN_WIDTH / 2.0f;
double lastY = SCREEN_HEIGHT / 2.0f;

glm::vec3 lightPos = glm::vec3(2.0f, 0.0f, -2.0f);

int main() {
	//******************************BOILER PLATE**************************
	if (!glfwInit()) {
		cout << "GLFW Initialization Failed!" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Yousuf Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwSwapInterval(1);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cout << "GLEW Initialization Failed!" << endl;
		return -1;
	}

	cout << "OPENGL Version : " << glGetString(GL_VERSION) << endl;


	//******************************BOILER PLATE***************************
	
	GLfloat positions[] = {
	-0.5f, -0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,		  0.0f,  0.0f, 1.0f,		0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		  0.0f,  0.0f, 1.0f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		  0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		  0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		  0.0f,  0.0f, 1.0f,		0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		  0.0f,  0.0f, 1.0f,		0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,		 -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		 -1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		 -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		 -1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		 -1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		 -1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,		  1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		  1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,		  1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,		  1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		  1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		  1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,		  0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,		  0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		  0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		  0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,		  0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		  0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,		  0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,		  0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		  0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		  0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		  0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		  0.0f,  1.0f,  0.0f,		0.0f, 1.0f
	};

	VertexArray cubeVAO;
	VertexBuffer cubeVB(positions,8 * 6 * 6 * sizeof(float));
	MyShader cubeShader("resources/shaders/test2.shader");
	Texture tex("resources/textures/rubiksCube.png",GL_RGBA,4);
	VertexBufferLayout cubeLayout;
	cubeLayout.Push<float>(3);//ppositions
	cubeLayout.Push<float>(3);//normals
	cubeLayout.Push<float>(2);//texture coord
	cubeVAO.AddBuffer(cubeVB, cubeLayout);

	VertexArray lightVAO;
	VertexBufferLayout lightCubeLayout;
	MyShader lightCubeShader("resources/shaders/lightCube.shader");
	lightCubeLayout.Push<float>(3);	//positions
	lightCubeLayout.Push<float>(3);	//normals
	lightCubeLayout.Push<float>(2);	//texture coord
	lightVAO.AddBuffer(cubeVB, lightCubeLayout);


	camera.initMouse(window);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glEnable(GL_DEPTH_TEST);
	

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		
		camera.getDeltaTimeStamp();

		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.5f));
		model = glm::scale(model,glm::vec3(3.0f));
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(camera.zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		cubeShader.Bind();
		cubeVAO.Bind();
		tex.Bind();
		cubeVB.Bind();
		cubeShader.SetUniformMat4fv("model", model);
		cubeShader.SetUniformMat4fv("view", view);
		cubeShader.SetUniformMat4fv("proj", proj);
		cubeShader.SetUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
		cubeShader.SetUniform3f("lightColor2", 1.0f, 0.0f, 1.0f);
		cubeShader.SetUniform3f("cubeColor", 1.0f, 0.5f, 0.31f);
		cubeShader.SetUniform1i("rubiksTexture", 0);
		cubeShader.SetUniformVEC3("lightPos", lightPos);
		cubeShader.SetUniform3f("lightPos2", 0.0f, lightPos.z, lightPos.x);
		cubeShader.SetUniformVEC3("viewPos", camera.Position);

		glm::vec3 ambient = glm::vec3(1.0f,1.0f,1.0f);
		glm::vec3 diffuse = glm::vec3(0.55f, 0.55f, 0.55f);
		glm::vec3 specular = glm::vec3(0.70f, 0.70f, 0.70f);
		int shininess = 32;
		cubeShader.SetUniformVEC3("material.ambient", ambient);
		cubeShader.SetUniformVEC3("material.diffuse", diffuse);
		cubeShader.SetUniformVEC3("material.specular", specular);
		cubeShader.SetUniform1i("material.shininess", shininess); 

		cubeShader.SetUniform3f("light.ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.SetUniform3f("light.diffuse", 0.55f, 0.55f, 0.55f);
		cubeShader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glm::mat4 lightcubemodel = glm::mat4(1.0f);
		lightcubemodel = glm::translate(lightcubemodel, lightPos);
		lightcubemodel = glm::scale(lightcubemodel, glm::vec3(0.2f));
		lightCubeShader.Bind();
		lightVAO.Bind();
		cubeVB.Bind();
		lightCubeShader.SetUniformMat4fv("cubemodel", lightcubemodel);
		lightCubeShader.SetUniformMat4fv("view", view);
		lightCubeShader.SetUniformMat4fv("proj", proj);
		lightCubeShader.SetUniform3f("lightCubeColor", 1.0f, 1.0f, 0.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glm::mat4 lightcubemodel2 = glm::mat4(1.0f);
		lightcubemodel2 = glm::translate(lightcubemodel2, glm::vec3(0.0f, lightPos.z ,lightPos.x));
		lightcubemodel2 = glm::scale(lightcubemodel2, glm::vec3(0.2f));
		lightCubeShader.Bind();
		lightVAO.Bind();
		cubeVB.Bind();
		lightCubeShader.SetUniformMat4fv("cubemodel", lightcubemodel2);
		lightCubeShader.SetUniformMat4fv("view", view);
		lightCubeShader.SetUniformMat4fv("proj", proj);
		lightCubeShader.SetUniform3f("lightCubeColor", 1.0f, 0.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightPos.x = 4 * glm::sin(glfwGetTime() * 2);
		lightPos.z = 4 * glm::cos(glfwGetTime() * 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	camera.processWindowKeys(window);
}



void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {            //for the first time to handle sudden jump
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	//now identify the offset since last  mouse change happened
	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;        //reversed since y coord go from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.processOffsetMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.processOffsetScroll(yoffset);
}