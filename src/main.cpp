#include "Config.h"

#include "Renderer.h"

#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	window = glfwCreateWindow(1600, 1200, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-100.0f, -100.0f, 0.0f, 0.0f,
		100.0f, -100.0f, 1.0f, 0.0f,
		100.0f, 100.0f, 1.0f, 1.0f,
		-100.0f, 100.0f, 0.0f, 1.0f
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//automatically binds in the constructor
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//automatically binds in the constructor
	IndexBuffer ib(indices, 6);

	// Windows
	// Shader shader("../../shaders/default.vert", "../../shaders/default.frag");
	// Linux



	std::string vertexPath("../shaders/default.vert");
	std::string fragmentPath ("../shaders/default.frag");
	// if windows
	#ifdef _WIN32
		vertexPath.insert(0, "../");
		fragmentPath.insert(0, "../");
	#endif
	Shader shader(vertexPath, fragmentPath);
	shader.Bind();


	// glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	glm::mat4 proj = glm::ortho(0.0f, 1600.0f, 0.0f, 1200.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	// glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

	// glm::mat4 mvp = proj * view * model;
	
	// shader.SetUniformMat4f("u_MVP", proj);

	float r = 0.0f;
	float increment = 0.05f;

	// glEnable(GL_DEBUG_OUTPUT);
	// glDebugMessageCallback(errorOccurredGL, NULL);


	//Windows
	// Texture texture("../../uv.png");
	// Linux

	std::string texturePath("../uv.png");
	#ifdef _WIN32
		texturePath.insert(0, "../");
	#endif
	Texture texture(texturePath);
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);

	Renderer renderer;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();


	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	ImGui_ImplOpenGL3_Init("#version 460");


	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(400, 200, 0);

	//swap interval
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, shader);
		}
		

		glm::vec4 color(r, 0.3f, 0.8f, 1.0f);
		// shader.Bind();
		// shader.SetUniform4f("u_Color", color);



		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;





		// ImGui
		{
			ImGui::Begin("Settings");
			ImGui::ColorEdit4("Square Color", glm::value_ptr(color));
			ImGui::SliderFloat3("Translation A", glm::value_ptr(translationA), 0.0f, 1600.0f);
			ImGui::SliderFloat3("Translation B", glm::value_ptr(translationB), 0.0f, 1600.0f);
			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// infinite loop opengl error checking
	// glfwTerminate();
	return 0;
}
