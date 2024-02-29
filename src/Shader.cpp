#include "Shader.h"

// std::string fileToString(const char* filename)
// {
// 	std::ifstream in(filename, std::ios::binary);
// 	if (in)
// 	{
// 		std::string contents;
// 		in.seekg(0, std::ios::end);
// 		contents.resize(in.tellg());
// 		in.seekg(0, std::ios::beg);
// 		in.read(&contents[0], contents.size());
// 		in.close();
// 		return(contents);
// 	}
// 	throw(errno);
// }

// // Constructor that build the Shader Program from 2 different shaders
// Shader::Shader(const char* vertexPath, const char* fragmentPath)
// {
// 	// Read vertexPath and fragmentPath and store the strings
// 	std::string vertexCode = fileToString(vertexPath);
// 	std::string fragmentCode = fileToString(fragmentPath);

// 	// Convert the shader source strings into character arrays
// 	const char* vertexSource = vertexCode.c_str();
// 	const char* fragmentSource = fragmentCode.c_str();

// 	// Create Vertex Shader Object and get its reference
// 	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 	// Attach Vertex Shader source to the Vertex Shader Object
// 	glShaderSource(vertexShader, 1, &vertexSource, NULL);
// 	// Compile the Vertex Shader into machine code
// 	glCompileShader(vertexShader);

// 	// Create Fragment Shader Object and get its reference
// 	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// 	// Attach Fragment Shader source to the Fragment Shader Object
// 	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
// 	// Compile the Vertex Shader into machine code
// 	glCompileShader(fragmentShader);

// 	// Create Shader Program Object and get its reference
// 	ID = glCreateProgram();
// 	// Attach the Vertex and Fragment Shaders to the Shader Program
// 	glAttachShader(ID, vertexShader);
// 	glAttachShader(ID, fragmentShader);
// 	// Wrap-up/Link all the shaders together into the Shader Program
// 	glLinkProgram(ID);

// 	// Delete the now useless Vertex and Fragment Shader objects
// 	glDeleteShader(vertexShader);
// 	glDeleteShader(fragmentShader);
// }

// // Activates the Shader Program
// void Shader::Activate()
// {
// 	glUseProgram(ID);
// }

// // Deletes the Shader Program
// void Shader::Delete()
// {
// 	glDeleteProgram(ID);
// }


// GLint	Shader::GetUniformLocation(const std::string& name) const
// {
// 	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
// 		return m_UniformLocationCache[name];
// 	GLint location = glGetUniformLocation(ID, name.c_str());
// 	if (location == -1)
// 	{
// 		std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
// 		return -1;
// 	}
// 	m_UniformLocationCache[name] = location;
// 	return location;
// }

// void Shader::SetUniform1i(const std::string& name, int value)
// {
// 	GLint location = GetUniformLocation(name);
// 	if (location != -1)
// 		glUniform1i(location, value);
// }




Shader::Shader()
	: m_RendererID(0)
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
	: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath), m_RendererID(0)
{
	m_RendererID = CreateShader(vertexPath, fragmentPath);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath), m_RendererID(0)
{
	m_RendererID = CreateShader(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void	Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void	Shader::Unbind() const
{
	glUseProgram(0);
}

GLuint	Shader::CompileShader(GLuint type, const std::string& source)
{
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

std::string	fileToString(const std::string& filename)
{
	std::ifstream in(filename.c_str(), std::ios::binary);
	if (!in)
	{
		std::cerr << "Error: file not found" << std::endl;
		exit(1);
	}
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

GLuint	Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, fileToString(vertexShader));
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fileToString(fragmentShader));

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}



GLint	Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
	{
		std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
		return -1;
	}
	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1)
		glUniform1i(location, value);
}

void	Shader::SetUniform4f(const std::string& name, glm::vec4 vector)
{
	GLint location = GetUniformLocation(name);
	if (location != -1)
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void	Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) // collum major no no transpose matrix
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}