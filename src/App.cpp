#include "App.h"

App::App(int width, int height, const char* title)
	: m_Width(width), m_Height(height)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_WindowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_WindowHandle)
	{
		glfwTerminate();
		std::cerr << "Failed to create window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_WindowHandle);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//? init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	// ImGuiIO& io = ImGui::GetIO(); (void)io;


	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
	ImGui_ImplOpenGL3_Init("#version 460");


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

App::~App()
{
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
