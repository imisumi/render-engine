#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <unordered_map>

// class Shader
// {
// 	public:
// 	GLuint ID;

// 	Shader() {}
// 	Shader(const char* vertexPath, const char* fragmentPath);

// 	void Activate();
// 	void Delete();

// 	void SetUniform1i(const std::string& name, int value);


// 	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

// 	GLint	GetUniformLocation(const std::string& name) const;
// };


class Shader
{
public:
	// deleete default constructor
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void	Bind() const;
	void	Unbind() const;


	// Set Uniforms
	void	SetUniform1i(const std::string& name, int value);

	void	SetUniform4f(const std::string& name, glm::vec4 vector);




private:
	GLuint	CompileShader(GLuint type, const std::string& source);
	GLuint	CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLint	GetUniformLocation(const std::string& name) const;

	std::string m_VertexPath;
	std::string m_FragmentPath;
	GLuint m_RendererID;

	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
};
