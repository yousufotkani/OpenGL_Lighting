#include"Texture.h"

Texture::Texture(const std::string& texturePath, GLenum pixelFormat,int channels) {
	glGenTextures(1, &renderer_id);
	glBindTexture(GL_TEXTURE_2D, renderer_id);
	
	GLCALL(data = stbi_load(texturePath.c_str(), &width, &height, &noChannels,channels));
	if (!data) std::cout << "data is NULL" << std::endl;

	stbi_set_flip_vertically_on_load(true);

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	std::cout << "height : " << height << std::endl;
	std::cout << "width : " << width << std::endl;

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data));
	GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

	//glEnable(GL_BLEND);// you enable blending function
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLCALL(stbi_image_free(data));
}

Texture::~Texture() {
	glDeleteTextures(1, &renderer_id);
}

void Texture::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, renderer_id);
}

void Texture::UnBind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}