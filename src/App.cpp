#include "App.h"

#include "Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "tests/TestClearColor/TestClearColor.h"
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


	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	 // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		 // Enable Docking
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	   // Enable Multi-Viewport / Platform Windows //? Crash???
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}


	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

App::~App()
{
}

App& App::Get()
{
	return *s_AppInstance;
}



void	RenderDocking()
{
	static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		{
			ImGui::Begin("DockSpace Demo", nullptr, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Options"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows,
					// which we can't undo at the moment without finer window depth/z control.
					ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
					ImGui::MenuItem("Padding", NULL, &opt_padding);
					ImGui::Separator();

					if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
					if (ImGui::MenuItem("Flag: NoDockingSplit",		 "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0))			 { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
					if (ImGui::MenuItem("Flag: NoUndocking",			"", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0))				{ dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
					if (ImGui::MenuItem("Flag: NoResize",			   "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))				   { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
					if (ImGui::MenuItem("Flag: AutoHideTabBar",		 "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))			 { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
					if (ImGui::MenuItem("Flag: PassthruCentralNode",	"", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
					ImGui::Separator();

					ImGui::EndMenu();
				}
				// HelpMarker(
				//	 "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
				//	 "- Drag from window title bar or their tab to dock/undock." "\n"
				//	 "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
				//	 "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
				//	 "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
				//	 "This demo app has nothing to do with enabling docking!" "\n\n"
				//	 "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
				//	 "Read comments in ShowExampleAppDockSpace() for more details.");

				ImGui::EndMenuBar();
			}
		}

		ImGui::End();
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
		RenderDocking();

		
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


		

		// ImGui::Begin("Settings");

		// ImGui::End();


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
