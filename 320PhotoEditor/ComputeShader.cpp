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

void ComputeShader::printComputeStats()
{
	int max_compute_work_group_count[3];
	int max_compute_work_group_size[3];
	int max_compute_work_group_invocations;

	for (int idx = 0; idx < 3; idx++) {
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, idx, &max_compute_work_group_count[idx]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, idx, &max_compute_work_group_size[idx]);
	}
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_compute_work_group_invocations);

	std::cout << "max work groups X " << max_compute_work_group_count[0] << std::endl;
	std::cout << "max work groups Y " << max_compute_work_group_count[1] << std::endl;
	std::cout << "max work groups Z " << max_compute_work_group_count[2] << std::endl;

	std::cout << "max work group X " << max_compute_work_group_size[0] << std::endl;
	std::cout << "max work group Y " << max_compute_work_group_size[1] << std::endl;
	std::cout << "max work group Z " << max_compute_work_group_size[2] << std::endl;

	std::cout << "max invocations in a single local work group that may be dispatched to a compute shader " << max_compute_work_group_invocations << std::endl;

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
