// #include "glad/glad.h"


// #include "GLFW/glfw3.h"

// #include "imgui.h"

// #include <iostream>
// #include <string>

// int main() {
// 	std::cout << "Hello, World!" << std::endl;


// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


// 	if (!glfwInit())
// 	{
// 		std::cout << "Failed to initialize GLFW" << std::endl;
// 		return -1;
// 	}
// 	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello, World!", NULL, NULL);
// 	if (!window)
// 	{
// 		std::cout << "Failed to create GLFW window" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}
// 	glfwMakeContextCurrent(window);

// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
// 	{
// 		std::cout << "Failed to initialize GLAD" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}

// 	IMGUI_CHECKVERSION();

// 	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
// 	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;


// 	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);




// 	glfwSwapInterval(0);
// 	double prevTime = 0.0;
// 	double currTime = 0.0;
// 	double deltaTime = 0.0;
// 	uint32_t frameCount = 0;
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		currTime = glfwGetTime();
// 		deltaTime = currTime - prevTime;
// 		frameCount++;
// 		if (deltaTime >= 1.0 / 15.0)
// 		{
// 			std::string FPS = std::to_string((1.0f / deltaTime) * frameCount);
// 			std::string ms = std::to_string((deltaTime / frameCount) * 1000.0f);
// 			std::string title = "FPS: " + FPS.substr(0, FPS.find('.')) + " ms: " + ms;
// 			glfwSetWindowTitle(window, title.c_str());
// 			frameCount = 0;
// 			prevTime = currTime;
// 		}


// 		glfwPollEvents();

// 		// glUseProgram(shader);
// 		glClear(GL_COLOR_BUFFER_BIT);
// 		// triangle->draw();
// 		glfwSwapBuffers(window);
// 	}

// 	glfwTerminate();


// 	return 0;
// }

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// #include "Application.h"


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// 3.0+ only

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
	if (window == nullptr)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	 // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		 // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	   // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//? My code goes here
		ImGui::Begin("Settings");
		ImGui::Button("Hello");
		ImGui::End();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}




	// while (!glfwWindowShouldClose(window))
	// {

	// 	glfwPollEvents();

	// 	// Start the Dear ImGui frame
	// 	ImGui_ImplOpenGL3_NewFrame();
	// 	ImGui_ImplGlfw_NewFrame();
	// 	ImGui::NewFrame();

	// 	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	// 	if (show_demo_window)
	// 		ImGui::ShowDemoWindow(&show_demo_window);

	// 	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	// 	{
	// 		static float f = 0.0f;
	// 		static int counter = 0;

	// 		ImGui::Begin("Hello, world!");						  // Create a window called "Hello, world!" and append into it.

	// 		ImGui::Text("This is some useful text.");			   // Display some text (you can use a format strings too)
	// 		ImGui::Checkbox("Demo Window", &show_demo_window);	  // Edit bools storing our window open/close state
	// 		ImGui::Checkbox("Another Window", &show_another_window);

	// 		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);			// Edit 1 float using a slider from 0.0f to 1.0f
	// 		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	// 		if (ImGui::Button("Button"))							// Buttons return true when clicked (most widgets return true when edited/activated)
	// 			counter++;
	// 		ImGui::SameLine();
	// 		ImGui::Text("counter = %d", counter);

	// 		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	// 		ImGui::End();
	// 	}

	// 	// 3. Show another simple window.
	// 	if (show_another_window)
	// 	{
	// 		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	// 		ImGui::Text("Hello from another window!");
	// 		if (ImGui::Button("Close Me"))
	// 			show_another_window = false;
	// 		ImGui::End();
	// 	}

	// 	// Rendering
	// 	ImGui::Render();
	// 	int display_w, display_h;
	// 	glfwGetFramebufferSize(window, &display_w, &display_h);
	// 	glViewport(0, 0, display_w, display_h);
	// 	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// 	// Update and Render additional Platform Windows
	// 	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	// 	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	// 	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	// 	{
	// 		GLFWwindow* backup_current_context = glfwGetCurrentContext();
	// 		ImGui::UpdatePlatformWindows();
	// 		ImGui::RenderPlatformWindowsDefault();
	// 		glfwMakeContextCurrent(backup_current_context);
	// 	}

	// 	glfwSwapBuffers(window);
	// }