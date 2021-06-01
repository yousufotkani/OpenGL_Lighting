#pragma once

#include<GL/glew.h>

class IndexBuffer {
private:
	unsigned int renderer_id;
	//unsigned int m_count;
public:
	IndexBuffer(const unsigned int *data, int count);
	~IndexBuffer();

	void Bind();
	void Unbind();
};