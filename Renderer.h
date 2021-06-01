#pragma once

#include<GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) clearError();\
				  x;\
				  ASSERT(checkError(#x,__LINE__,__FILE__))


void clearError();
bool checkError(const char* function, int line, const char* file);