#pragma once

#include<GL/glew.h>
#include"stb_image/stb_image.h"

#include"Renderer.h"

#include<iostream>
#include<string>

class Texture {
private:
	unsigned int renderer_id;
	int width, height, noChannels;
	unsigned char* data;

public:
	Texture(const std::string& texturePath, GLenum pixelFormat,int channels);
	~Texture();


	void Bind(unsigned int slot = 0);
	void UnBind();

	int GetHeight() { return height; }
	int GetWidth() { return width; }
};