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

