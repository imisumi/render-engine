#include "App.h"


static App* s_Instance = nullptr;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace ShaderTemp
{
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
}

App::App()
{
	s_Instance = this;

	m_Scene = new Scene();

	Init();
}

App::~App()
{
	s_Instance = nullptr;

	Shutdown();
}

App& App::Get()
{
	return *s_Instance;
}

void App::Init()
{
	// Initialize GLFW
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	// Set OpenGL version to 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 3.0+ only

	// Create a new GLFW window
	m_WindowHandle = glfwCreateWindow(m_Width, m_Height, "OpenGL", nullptr, nullptr);
	if (!m_WindowHandle)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_WindowHandle);

	// Load OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Enable VSync
	glfwSwapInterval(1);

	// Set the clear color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// // Enable depth testing
	// glEnable(GL_DEPTH_TEST);

	int width, height;
	glfwGetFramebufferSize(m_WindowHandle, &width, &height);
	glViewport(0, 0, width, height);






	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	// Create a shader program
	m_Shader = Shader("../../shaders/default.vert", "../../shaders/default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(m_Shader.ID, "scale");



	Texture img("../../uv.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	img.texUnit(m_Shader, "tex", 0);



	// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(m_WindowHandle))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		m_Shader.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(m_Shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(m_Shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(m_Shader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		img.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(m_WindowHandle);
		// Take care of all GLFW events
		glfwPollEvents();
	}
}

void	App::OnInput()
{
	// std::cout << "windowHandle: " << m_WindowHandle << std::endl;
	if (glfwGetKey(m_WindowHandle, GLFW_KEY_W) == GLFW_PRESS)
	{
		std::cout << "W" << std::endl;
	
	}

}


void App::Shutdown()
{
	glfwDestroyWindow(m_WindowHandle);
	glfwTerminate();
}

void App::Run()
{

}


