#pragma once
#include"GL/glew.h"
//#include<vector>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int renderer_id;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb,VertexBufferLayout& layout);
	void Bind();
	void Unbind();

};