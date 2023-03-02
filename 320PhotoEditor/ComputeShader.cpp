#include "ComputeShader.h"

ComputeShader::ComputeShader(const char* path)
{
	compile(path);
}

ComputeShader::ComputeShader(unsigned int ID)
{
	this->ID = ID;
}

void ComputeShader::use()
{
	use(ID);
}

void ComputeShader::use(unsigned int ID)
{
	glUseProgram(ID);
}

void ComputeShader::compile(const char* path)
{
	std::ifstream shaderFile;
	shaderFile.open(path);

	if (!shaderFile.is_open())
	{
		std::cerr << "Error: unable to open shader file: " << path << std::endl;
	}

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();

	shaderFile.close();

	std::string sshaderCode = shaderStream.str();
	const char* shaderCode = sshaderCode.c_str();

	unsigned int compute;
	int success;
	char infoLog[512];
	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &shaderCode, NULL);
	glCompileShader(compute);
	checkCompileErrors(compute);

	ID = glCreateProgram();
	glAttachShader(ID, compute);
	glLinkProgram(ID);
	checkCompileErrors(compute);
	glDeleteShader(compute);
}

void ComputeShader::checkCompileErrors(unsigned int shader)
{
	GLint success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cerr << "Compute Shader Compile Error: " << "\n" << infoLog << std::endl;
	}
}
