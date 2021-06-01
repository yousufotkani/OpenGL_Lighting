#include"IndexBuffer.h"
#include"Renderer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, int count) {
	GLCALL(glGenBuffers(1, &renderer_id));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::Bind() {
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}

void IndexBuffer::Unbind() {
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}