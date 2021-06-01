#include"VertexBuffer.h"
#include"Renderer.h"


VertexBuffer::VertexBuffer(GLfloat* data, int size) {
	GLCALL(glGenBuffers(1, &renderer_id));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer:: Bind() {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}

void VertexBuffer::Unbind() {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER,0));
}