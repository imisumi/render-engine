// #include "Config.h"

// #include "Renderer.h"

#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "App.h"


#include "tests/Test.h"
#include "tests/TestClearColor/TestClearColor.h"
#include "tests/TestTexture2D/TestTexture2D.h"
#include "tests/TestCamera/TestCamera.h"

// #include "Window.h"


// static App* s_AppInstance = nullptr;

// App& GetApp()
// {
// 	return *s_AppInstance;
// }

// GLFWwindow* window = nullptr;

// namespace WIndow
// {
// 	GLFWwindow& GetWindow()
// 	{
// 		return *window;
// 	}
// }


int main()
{
	App app(1600, 1200, "OpenGL");
	app.Run();
	return 0;


	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(1600, 1200, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	// s_AppInstance = new App();
	// s_AppInstance->SetWindow(window);



	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;


	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));



	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");



	tests::Test* currentTest = nullptr;
	tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
	// testMenu->m_WindowHandle = window;
	currentTest = testMenu;


	testMenu->RegisterTest<tests::TestClearColor>("Clear Color");
	testMenu->RegisterTest<tests::TestTexture2D>("Texture 2D");
	testMenu->RegisterTest<tests::TestCamera>("TestCamera");

	// set default test clear color
	// std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	//find the test with the name "Clear Color" and set it as the current test
	currentTest = testMenu->FindTest("TestCamera");

	
	double prevFrameTime = glfwGetTime();
	Renderer renderer;
	//swap interval
	while (!glfwWindowShouldClose(window))
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
		float deltaTime = static_cast<float>(currentTime - prevFrameTime);
		prevFrameTime = currentTime;
//?----------------------------------------------
//?     ImGui code
		if (currentTest)
		{
			currentTest->OnUpdate(deltaTime);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				std::cout << "back" << std::endl;
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}


//?----------------------------------------------
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
//?----------------------------------------------
	}

	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// infinite loop opengl error checking
	// glfwTerminate();
	return 0;
}
