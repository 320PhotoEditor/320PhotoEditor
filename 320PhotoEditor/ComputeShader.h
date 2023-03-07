#pragma once

#include "Common.h"
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#else

#endif

#include <GL/glew.h>
#include <GL/GL.h>

class ComputeShader
{
public:

	ComputeShader(const char* path);
	ComputeShader(unsigned int ID);

	void use();

	static void use(unsigned int ID);

	static void printComputeStats();

private:

	unsigned int ID;

	void compile(const char* path);

	void checkCompileErrors(unsigned int shader);
};

