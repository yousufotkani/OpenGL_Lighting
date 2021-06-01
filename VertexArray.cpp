#include"VertexArray.h"

VertexArray::VertexArray() {
	GLCALL(glGenVertexArrays(1, &renderer_id));
	//GLCALL(glBindVertexArray(renderer_id));
}

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	//std::vector<VertexBufferElement> elem = layout.GetElements();
	const auto& elem = layout.GetElements();
	for(unsigned int i=0;i<elem.size();i++){
		const auto& element = elem[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i,element.count,element.type,
			element.normalized,layout.GetStride(),(const void *)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() {
	GLCALL(glBindVertexArray(renderer_id));
}

void VertexArray::Unbind() {
	GLCALL(glBindVertexArray(0));
}

VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &renderer_id));
}