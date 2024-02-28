#include "App.h"


static App* s_Instance = nullptr;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace Shader
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
	// glfwSetErrorCallback(glfw_error_callback);
	// if (!glfwInit())
	// {
	// 	std::cout << "Failed to initialize GLFW" << std::endl;
	// 	return;
	// }

	// // Set OpenGL version to 4.6
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 3.2+ only
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 3.0+ only

	// // Create a new GLFW window
	// m_WindowHandle = glfwCreateWindow(m_Width, m_Height, "OpenGL", nullptr, nullptr);
	// if (!m_WindowHandle)
	// {
	// 	std::cout << "Failed to create GLFW window" << std::endl;
	// 	return;
	// }

	// glfwMakeContextCurrent(m_WindowHandle);

	// // Load OpenGL functions
	// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	// {
	// 	std::cout << "Failed to initialize GLAD" << std::endl;
	// 	return;
	// }

	// // Enable VSync
	// glfwSwapInterval(1);

	// // Set the clear color
	// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// // Enable depth testing
	// glEnable(GL_DEPTH_TEST);

	// int width, height;
	// glfwGetFramebufferSize(m_WindowHandle, &width, &height);
	// glViewport(0, 0, width, height);



	// //temp
	// m_Program = Shader::makeProgram("../../shaders/default.vert", "../../shaders/default.frag");

	// m_Triangle = new TriangleMesh();
	// m_Material = new Material("../../uv.png");

	// glUseProgram(m_Program);
	// glUniform1i(glGetUniformLocation(m_Program, "material"), 0);

	// // aplha blending
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// m_Scene->m_Camera.SetPosition(glm::vec3(-5.0f, 0.0f, 3.0f));
	// m_Scene->m_Camera.SetDirection(glm::vec3(1.0f, 0.0f, 0.0f));
	// m_Scene->m_Camera.setUpDirection(glm::vec3(0.0f, 0.0f, 1.0f));



	// glm::vec3 m_QuadPos = glm::vec3(-0.2f, 0.4f, 0.0f);
	// glm::vec3 cameraPos = glm::vec3(-5.0f, 0.0f, 3.0f);
	// glm::vec3 cameraTarget = glm::vec3(1.0f, 0.0f, 0.0f);
	// glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

	// GLuint m_ModelLoc = glGetUniformLocation(m_Program, "model");
	// GLuint viewLoc = glGetUniformLocation(m_Program, "view");
	// GLuint projLoc = glGetUniformLocation(m_Program, "projection");

	// glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
	// glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// glm::mat4 proj = glm::perspective(
	// 		glm::radians(45.0f), 
	// 		(float)m_Width / (float)m_Height, 0.1f, 1000.0f);
	// glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));



	// m_Scene->m_Camera.RecalculateView();










	int screenWidth = 1600;
	int screenHeight = 1200;
	// std::ifstream file;
	// std::string vertexShaderSource;
	
	// file.open("../../shaders/default.vert");
	// while (std::getline(file, vertexShaderSource))
	// {
	// 	std::cout << vertexShaderSource << std::endl;
	// }


	
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 3.0+ only

	GLFWwindow*	m_WindowHandle = glfwCreateWindow(screenWidth, screenHeight, "Render Engine", NULL, NULL);
	if (!m_WindowHandle)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_WindowHandle);




	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	int width, height;

	GLuint program = Shader::makeProgram("../../shaders/default.vert", "../../shaders/default.frag");

	TriangleMesh* triangle = new TriangleMesh();
	Material* material = new Material("../../uv.png");

	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "material"), 0);

	// aplha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	m_Scene->m_Camera.SetPosition(glm::vec3(-5.0f, 0.0f, 3.0f));
	m_Scene->m_Camera.SetDirection(glm::vec3(1.0f, 0.0f, 0.0f));
	m_Scene->m_Camera.setUpDirection(glm::vec3(0.0f, 0.0f, 1.0f));


	glm::vec3 quadPos = glm::vec3(-0.2f, 0.4f, 0.0f);
	// glm::vec3 cameraPos = glm::vec3(-5.0f, 0.0f, 3.0f);
	// glm::vec3 cameraTarget = glm::vec3(1.0f, 0.0f, 0.0f);
	// glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

	GLuint modelLoc = glGetUniformLocation(program, "model");
	GLuint viewLoc = glGetUniformLocation(program, "view");
	GLuint projLoc = glGetUniformLocation(program, "projection");

	;
	// glm::mat4 view = glm::lookAt(m_Scene->m_Camera.getPosition(), m_Scene->m_Camera.getDirection(), m_Scene->m_Camera.getUpDirection());
	// m_Scene->m_Camera.setView(view);
	m_Scene->m_Camera.RecalculateView();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_Scene->m_Camera.GetView()));

	glm::mat4 proj = glm::perspective(
			glm::radians(45.0f), 
			(float)screenWidth / (float)screenHeight, 0.1f, 1000.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));



	while (!glfwWindowShouldClose(m_WindowHandle))
	{
		glfwPollEvents();
		//resize
		glfwGetFramebufferSize(m_WindowHandle, &width, &height);
		if (width != screenWidth || height != screenHeight)
		{
			glViewport(0, 0, width, height);
			screenWidth = width;
			screenHeight = height;
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, quadPos);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// if (Input::IsKeyDown(GLFW_KEY_W))
		// {
		// 	std::cout << "W" << std::endl;
		// }

		// glfw key input
		// if (glfwGetKey(m_WindowHandle, GLFW_KEY_W) == GLFW_PRESS)
		// {
		// 	std::cout << "W" << std::endl;
		// }

		// if (glfwGetKey(m_WindowHandle, GLFW_KEY_W) == GLFW_PRESS)
		// {
		// 	std::cout << "W" << std::endl;
		// }

		// OnInput();
		std::cout << "windowHandle: " << m_WindowHandle << std::endl;


		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		material->use(0);
		triangle->draw();

		glfwSwapBuffers(m_WindowHandle);
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

	glm::vec3 QuadPos = glm::vec3(-0.2f, 0.4f, 0.0f);
	// ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// ImGuiIO& io = ImGui::GetIO();
	int	width, height;
	while (!glfwWindowShouldClose(m_WindowHandle))
	{
		glfwPollEvents();


		glfwGetFramebufferSize(m_WindowHandle, &width, &height);
		if (width != m_Width || height != m_Height)
		{
			glViewport(0, 0, width, height);
			m_Width = width;
			m_Height = height;
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, QuadPos);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(m_ModelLoc, 1, GL_FALSE, glm::value_ptr(model));

		OnInput();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_Program);
		m_Material->use(0);
		m_Triangle->draw();

		glfwSwapBuffers(m_WindowHandle);
	}
}


