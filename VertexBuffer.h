#pragma once

#include<GL/glew.h>

class VertexBuffer {
private:
	unsigned int renderer_id;
public:
	VertexBuffer(GLfloat* data, int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};