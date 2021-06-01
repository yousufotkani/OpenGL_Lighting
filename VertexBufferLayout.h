#pragma once
//#include<iostream>
#include<vector>
#include"Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch(type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		case GL_UNSIGNED_INT:	return 4;
		}
		return 0;
	}
};


class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() :m_stride(0) {}

	template<typename T>
	void Push(unsigned int size) {
		static_assert(false);
	}
	
	template<>
	void Push<float>(unsigned int size) {
		m_elements.push_back({ GL_FLOAT,size,GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * size;
	}

	template<>
	void Push<unsigned int>(unsigned int size) {
		m_elements.push_back({ GL_UNSIGNED_INT,size,GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * size;
	}

	template<>
	void Push<unsigned char>(unsigned int size) {
		m_elements.push_back({ GL_UNSIGNED_BYTE,size,GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * size;
	}

	const std::vector<VertexBufferElement> GetElements() { return m_elements; }
	unsigned int GetStride() { return m_stride; }

};