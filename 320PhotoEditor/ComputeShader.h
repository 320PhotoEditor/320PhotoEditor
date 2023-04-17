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
#define GL_FALSE false
#define GL_READ_WRITE 0
#define GL_RGBA8 0

inline void glDispatchCompute(unsigned int x, unsigned int y, unsigned int z) {}
inline void glMemoryBarrier(unsigned int a) {}
inline void glGetIntegeri_v(unsigned int a, unsigned int idx, int* b) {}
inline void glGetIntegerv(unsigned int a, int* b) {}
inline int glGetUniformLocation(int a, const char* b) { return 0; }
inline void glUniform1i(int a, int b) {}
inline void glUniform1f(int a, float b) {}
inline void glUniform2f(int a, float b, float c) {}
inline unsigned int glCreateShader(unsigned int a) { return 0; }
inline void glShaderSource(unsigned int id, unsigned int a, const char** b, int* c) {}
inline void glCompileShader(unsigned int id) {}
inline unsigned int glCreateProgram() { return 0; }
inline void glUseProgram(unsigned int id) {}
inline void glAttachShader(unsigned int id, unsigned int d) {}
inline void glLinkProgram(unsigned int id) {}
inline void glDeleteShader(unsigned int id) {}
inline void glGetShaderiv(unsigned int id, unsigned int a, int* c) {}
inline void glGetShaderInfoLog(unsigned int a, int b, int*, char* d) {}
inline void glBindImageTexture(unsigned int a, unsigned int b, unsigned int c, bool d, unsigned int e, unsigned int f, unsigned int g) {}

inline int glewInit() { return 0; }

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

	static int genBuffer();
	static void bindBuffer(unsigned int buf, unsigned int index);
	static void setBuffer(unsigned int buf, size_t size, void* data);

	static void printComputeStats();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const sf::Vector2f& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat3(const std::string& name, const Matrix3x3& mat) const;

	unsigned int ID;

private:

	void compile(const char* path);

	void checkCompileErrors(unsigned int shader);
};

