#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <unordered_map>

class Shader
{
	public:
	GLuint ID;

	Shader() {}
	Shader(const char* vertexPath, const char* fragmentPath);

	void Activate();
	void Delete();

	void SetUniform1i(const std::string& name, int value);


	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

	GLint	GetUniformLocation(const std::string& name) const;
};
