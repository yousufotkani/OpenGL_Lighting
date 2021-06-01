#include"Renderer.h"
#include <iostream>

using namespace std;

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool checkError(const char* function, int line, const char* file) {
	if (GLenum error = glGetError()) {
		cout << "An error has occured in the following line : " << line << endl;
		cout << "ERROR CODE : " << error << endl;
		cout << "FILE NAME : " << file << endl;
		cout << "FUNCTION : " << function << endl;

		return false;
	}

	return true;
}