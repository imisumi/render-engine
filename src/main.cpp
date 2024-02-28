#include "Config.h"

// GLuint	makeModule(const std::string& source, GLenum type)
// {
// 	GLuint shader = glCreateShader(type);
// 	const char* src = source.c_str();
// 	glShaderSource(shader, 1, &src, NULL);
// 	glCompileShader(shader);

// 	GLint success;
// 	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		GLchar infoLog[512];
// 		glGetShaderInfoLog(shader, 512, NULL, infoLog);
// 		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
// 	}

// 	return shader;
// }

GLuint	makeModule(const std::string& path, GLenum type)
{
	std::ifstream file;
	std::stringstream stream;
	std::string line;

	file.open(path);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	while (std::getline(file, line))
	{
		stream << line << '\n';
	}
	std::string source = stream.str();
	const char* src = source.c_str();
	line.clear();
	stream.clear();
	file.close();

	GLuint shader = glCreateShader(type);
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

// GLuint	makeProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
// {
// 	GLuint vertexShader = makeModule(vertexShaderSource, GL_VERTEX_SHADER);
// 	GLuint fragmentShader = makeModule(fragmentShaderSource, GL_FRAGMENT_SHADER);

// 	GLuint program = glCreateProgram();
// 	glAttachShader(program, vertexShader);
// 	glAttachShader(program, fragmentShader);
// 	glLinkProgram(program);

// 	GLint success;
// 	glGetProgramiv(program, GL_LINK_STATUS, &success);
// 	if (!success)
// 	{
// 		GLchar infoLog[512];
// 		glGetProgramInfoLog(program, 512, NULL, infoLog);
// 		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
// 	}

// 	glDeleteShader(vertexShader);
// 	glDeleteShader(fragmentShader);

// 	return program;
// }

GLuint	makeProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	std::vector<GLuint> modules;
	modules.push_back(makeModule(vertexShaderSource, GL_VERTEX_SHADER));
	modules.push_back(makeModule(fragmentShaderSource, GL_FRAGMENT_SHADER));

	GLuint program = glCreateProgram();
	for (GLuint module : modules)
	{
		glAttachShader(program, module);
	}
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	for (GLuint module : modules)
	{
		glDeleteShader(module);
	}

	return program;
}

#include "App.h"

int main()
{
	App *app = new App();
	app->Run();
	return 0;
}