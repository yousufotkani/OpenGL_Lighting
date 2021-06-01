#pragma once
#include<GL/glew.h>

#include"Renderer.h"

#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"

#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<unordered_map>

struct shaderStringSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class MyShader {
private:
	unsigned int renderer_id;
	std::string fileDir;
	std::unordered_map<std::string, int> GetUniformLocationCache;
public:
	MyShader(const std::string& filepath);
	~MyShader();
	void Bind();
	void UnBind();

	void SetUniform1i(const std::string& uniformName, int value);
	void SetUniformMat4fv(const std::string& uniformName, glm::mat4& mat);
	void SetUniform4f(const std::string& uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
	void SetUniform3f(const std::string& uniformName, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniformVEC3(const std::string& uniformName, glm::vec3 vec);
	void ViewShaderCode(const std::string& filepath);
private:
	shaderStringSource parseShader(std::string filepath);
	int compileShader(int type, std::string& source);
	unsigned int createShader(std::string& vertexShader, std::string& fragmentShader);
	int GetUniformLocation(const std::string& uniformName);
};