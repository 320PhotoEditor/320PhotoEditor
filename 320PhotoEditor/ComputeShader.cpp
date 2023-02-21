#include "ComputeShader.h"

ComputeShader::ComputeShader(const char* path)
{
	compile(path);
}

void ComputeShader::use()
{
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


}

void ComputeShader::checkCompileErrors()
{
}
