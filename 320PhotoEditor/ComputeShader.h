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
void glGetIntegeri_v(unsigned int a, unsigned int idx, int* b) {}
void glGetIntegerv(unsigned int a, int* b) {}
int glGetUniformLocation(int a, const char* b) { return 0; }
void glUniform1i(int a, int b) {}
void glUniform1f(int a, float b) {}
void glUniform2f(int a, float b, float c) {}
unsigned int glCreateShader(unsigned int a) { return 0; }
void glShaderSource(unsigned int id, unsigned int a, const char** b, int* c) {}
void glCompileShader(unsigned int id) {}
unsigned int glCreateProgram() { return 0; }
void glUseProgram(unsigned int id) {}
void glAttachShader(unsigned int id, unsigned int d) {}
void glLinkProgram(unsigned int id) {}
void glDeleteShader(unsigned int id) {}
void glGetShaderiv(unsigned int id, unsigned int a, int* c) {}
void glGetShaderInfoLog(unsigned int a, int b, int*, char* d) {}
void glBindImageTexture(unsigned int a, unsigned int b, unsigned int c, bool d, unsigned int e, unsigned int f, unsigned int g) {}

int glewInit() { return 0; }

#endif

class ComputeShader
{
public:

	ComputeShader(const char* path);
	ComputeShader(unsigned int ID);

	void use();

	void compute(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ);

	static void use(unsigned int ID);

	static void bindTexture(unsigned int texture, unsigned int binding);

	static void printComputeStats();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const sf::Vector2f& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

	unsigned int ID;

private:

	void compile(const char* path);

	void checkCompileErrors(unsigned int shader);
};

