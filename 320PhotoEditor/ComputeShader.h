#pragma once

#include "Common.h"
#include <fstream>
#include <sstream>

class ComputeShader
{
public:

	ComputeShader(const char* path);

	void use();

private:

	void compile(const char* path);

	void checkCompileErrors();
};

