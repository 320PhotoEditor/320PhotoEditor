#include "ComputeShader.h"

ComputeShader::ComputeShader(const char* path)
{
	glewInit();
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

void ComputeShader::compute(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ)
{
	glDispatchCompute(sizeX, sizeY, sizeZ);

	//wait til the shader is finished writing
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ComputeShader::use(unsigned int ID)
{
	glUseProgram(ID);
}

void ComputeShader::bindTexture(unsigned int texture)
{
	glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
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

void ComputeShader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ComputeShader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ComputeShader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ComputeShader::setVec2(const std::string& name, const sf::Vector2f& value) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void ComputeShader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
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
	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cerr << "Compute Shader Compile Error: " << "\n" << infoLog << std::endl;
	}
}
