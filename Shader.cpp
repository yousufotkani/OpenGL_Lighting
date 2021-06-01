#include"Shader.h"


using namespace std;

MyShader::MyShader(const std::string& filepath) : fileDir(filepath), renderer_id(0) {
	shaderStringSource source = parseShader(filepath);
	renderer_id = createShader(source.vertexSource, source.fragmentSource);
}


MyShader::~MyShader() { glDeleteProgram(renderer_id); }

void MyShader::Bind() {
	glUseProgram(renderer_id);
}

void MyShader::UnBind() {
	glDeleteProgram(renderer_id);
}

void MyShader::SetUniform1i(const std::string& uniformName, int value) {
	GLCALL(glUniform1i(GetUniformLocation(uniformName), value));
}

void MyShader::SetUniformMat4fv(const std::string& uniformName, glm::mat4& mat) {
	GLCALL(glUniformMatrix4fv(GetUniformLocation(uniformName),1,GL_FALSE,glm::value_ptr(mat)));
}

void MyShader::SetUniform4f(const std::string& uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) {
	int uniformLocation = GetUniformLocation(uniformName);
	GLCALL(glUniform4f(uniformLocation, v1, v2, v3, v4));
}


void MyShader::SetUniform3f(const std::string& uniformName, GLfloat v1, GLfloat v2, GLfloat v3) {
	int uniformLocation = GetUniformLocation(uniformName);
	GLCALL(glUniform3f(uniformLocation, v1, v2,v3));
}

void MyShader::SetUniformVEC3(const std::string& uniformName,glm::vec3 vec) {
	int uniformLocation = GetUniformLocation(uniformName);
	GLCALL(glUniform3f(uniformLocation,vec.x,vec.y,vec.z));
}

int MyShader::GetUniformLocation(const std::string& uniformName ) {
	if (GetUniformLocationCache.find(uniformName) != GetUniformLocationCache.end())
		return GetUniformLocationCache[uniformName];
	GLCALL(int location =  glGetUniformLocation(renderer_id, uniformName.c_str()) );
	if (location == -1)
		cout << "Warning : Uniform Location for "<< uniformName << " Location doesnt Exist" << endl;

	return location;

}

void MyShader::ViewShaderCode(const std::string& filepath) {
	shaderStringSource source = parseShader(filepath);
	cout << "vertex" << endl;
	cout << source.vertexSource << endl;
	cout << "fragment" << endl;
	cout << source.fragmentSource << endl;
}

shaderStringSource MyShader::parseShader(const std::string filepath) {
	ifstream stream(filepath);
	string line;
	stringstream ss[2];

	enum class shaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	shaderType type = shaderType::NONE;

	while(getline(stream,line)){
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos)
				type = shaderType::VERTEX;
			if (line.find("fragment") != string::npos)
				type = shaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };
}
int MyShader::compileShader(int type, std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id,1, &src, nullptr);
	glCompileShader(id);

	//TEST3 ERRORHANDLE
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char) * length);  //message[length];
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Error occured on " <<
			(type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << endl;
		cout << message << endl;
	}

	return id;
}


unsigned int MyShader::createShader(std::string& vertexShader, std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

