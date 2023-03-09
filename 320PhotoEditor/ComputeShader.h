#pragma once

#include "Common.h"
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#else

#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0
#define GL_COMPUTE_SHADER 0
#define GL_COMPILE_STATUS 0

void glDispatchCompute(unsigned int x, unsigned int y, unsigned int z) {}
void glMemoryBarrier(unsigned int a) {}
void glUseProgram(unsigned int id) {}
void glGetIntegeri_v(unsigned int a, unsigned int idx, &max_compute_work_group_count[idx]);
void glGetIntegeri_v(unsigned int a, unsigned int idx, &max_compute_work_group_size[idx]);
void glGetIntegerv(unsigned int a, &max_compute_work_group_invocations);

glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
glUniform2f
void glCreateShader(unsigned int a) {}
void glShaderSource(unsigned int id, unsigned int a, &shaderCode, NULL) {}
void glCompileShader(unsigned int id) {}

unsigned int glCreateProgram() { return 0; }
void glUseProgram(unsigned int id) {}
void glAttachShader(unsigned int id, unsigned int d) {}
void glLinkProgram(unsigned int id) {}
void glDeleteShader(unsigned int id) {}
void glGetShaderiv(unsigned int id, unsigned int a, &success);

glGetShaderInfoLog(shader, 1024, NULL, infoLog);

#endif

class ComputeShader
{
public:

	ComputeShader(const char* path);
	ComputeShader(unsigned int ID);

	void use();

	void compute(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ);

	static void use(unsigned int ID);

	static void printComputeStats();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const sf::Vector2f& value) const;
	void setVec2(const std::string& name, float x, float y) const;

private:

	unsigned int ID;

	void compile(const char* path);

	void checkCompileErrors(unsigned int shader);
};

