#include "App.h"

#include "Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "tests/TestClearColor/TestClearColor.h"
#include "tests/TestTexture2D/TestTexture2D.h"
#include "tests/TestCamera/TestCamera.h"

static App* s_AppInstance = nullptr;

App::App(int width, int height, const char* title)
	: m_Width(width), m_Height(height), m_Title(title)
{
	s_AppInstance = this;

	InitGLFW();
	InitGlad();
	InitImGui();

	//? setup test framework
	m_TestMenu = new tests::TestMenu(m_CurrentTest);
	m_CurrentTest = m_TestMenu;

	//? register tests
	m_TestMenu->RegisterTest<tests::TestClearColor>("Clear Color");
	m_TestMenu->RegisterTest<tests::TestTexture2D>("Texture 2D");
	m_TestMenu->RegisterTest<tests::TestCamera>("Camera");

	//? setup starter test
	m_CurrentTest = m_TestMenu->FindTest("Camera");
	if (!m_CurrentTest)
	{
		std::cerr << "Failed to find test" << std::endl;
		return;
	}

}

void	App::InitGLFW()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_WindowHandle = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_WindowHandle)
	{
		glfwTerminate();
		std::cerr << "Failed to create window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_WindowHandle);
	glfwSwapInterval(1);

	glfwSetWindowSizeLimits(m_WindowHandle, m_Width, m_Height, m_Width, m_Height);
}

void	App::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glViewport(0, 0, m_Width, m_Height));
}

void	App::InitImGui()
{
	//? init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	// ImGuiIO& io = ImGui::GetIO(); (void)io;


	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

App::~App()
{
}

App& App::Get()
{
	return *s_AppInstance;
}

void App::Run()
{
	Renderer renderer;
	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(m_WindowHandle))
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		renderer.Clear();
//?----------------------------------------------
//?     My Code


//?----------------------------------------------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Calculate delta time
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - prevTime);
		prevTime = currentTime;
//?----------------------------------------------
//?     ImGui code
		if (m_CurrentTest)
		{
			m_CurrentTest->OnUpdate(deltaTime);
			m_CurrentTest->OnRender();
			ImGui::Begin("Test");
			if (m_CurrentTest != m_TestMenu && ImGui::Button("<-"))
			{
				std::cout << "back" << std::endl;
				delete m_CurrentTest;
				m_CurrentTest = m_TestMenu;
				GLCall(glViewport(0, 0, m_Width, m_Height));
				glfwSetWindowSizeLimits(m_WindowHandle, m_Width, m_Height, m_Width, m_Height);
			}
			m_CurrentTest->OnImGuiRender();
			ImGui::End();
		}


//?----------------------------------------------
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_WindowHandle);
		glfwPollEvents();
//?----------------------------------------------
	}

	delete m_CurrentTest;
	if (m_CurrentTest != m_TestMenu)
		delete m_TestMenu;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
