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
// #define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
// #if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
// #pragma comment(lib, "legacy_stdio_definitions")
// #endif

// #include "Application.h"

#include <iostream>
#include "App.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

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
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 3.0+ only

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1600, 1200, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
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

	// glfw disable vsync
	glfwSwapInterval(0);



	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
	bool ret = LoadTextureFromFile("/home/imisumi/Desktop/render-engine/uv.png", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// if (show_demo_window)
		// 	ImGui::ShowDemoWindow(&show_demo_window);

		//? My code goes here
		// ImGui::Begin("Settings");
		// ImGui::Button("Hello");
		// ImGui::End();


		App::RenderUI();

		ImGui::Begin("fps");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();


		// ImGui::Begin("OpenGL Texture Text");
		// ImGui::Begin("OpenGL Texture Text", nullptr, ImGuiWindowFlags_NoScrollbar);


		// ImGui::Begin("OpenGL Texture Text", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		// // ImGui::Text("pointer = %p", my_image_texture);
		// static ImVec2 imagePosition(0.0f, 0.0f);
		// ImGui::Text("position = %f, %f", imagePosition.x, imagePosition.y);

		// if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
		// {
		// 	// If right mouse button is being dragged, update the image position
		// 	ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
		// 	imagePosition.x += mouseDelta.x;
		// 	imagePosition.y += mouseDelta.y;
		// }

		// // Draw the image with updated position
		// ImGui::SetCursorPos(imagePosition);

		// ImVec2 imageSize(my_image_width, my_image_height);
		// ImGui::Image((void*)(intptr_t)my_image_texture, imageSize);

		// ImGui::End();



		// ImGui::Begin("OpenGL Texture Text", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		// ImVec2 windowSize = ImGui::GetWindowSize();
		// ImGui::Text("Window Size: %.0f x %.0f", windowSize.x, windowSize.y);

		// static float scale = 1.0f; // Initial scale factor
		// // Adjust scale factor based on mouse scroll
		// scale += ImGui::GetIO().MouseWheel * 0.1f;

		// ImVec2 imageSize(my_image_width * scale, my_image_height * scale);

		// // static ImVec2 imageOrigin(windowSize.x / 2.0f, windowSize.y / 2.0f); // Set origin to center of window
		// static ImVec2 imageOrigin(100, 100); // Set origin to top-left of window

		// // Calculate image position to scale around imageOrigin
		// ImVec2 imagePosition = ImVec2(imageSize.x / 2.0f, imageSize.y / 2.0f);
		// imagePosition.x = imageOrigin.x - imagePosition.x;
		// imagePosition.y = imageOrigin.y - imagePosition.y;
		// // ImVec2 imagePosition = imageOrigin - ImVec2(imageSize.x / 2.0f, imageSize.y / 2.0f);

		// if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
		// {
		// 	ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
		// 	imageOrigin.x += mouseDelta.x;
		// 	imageOrigin.y += mouseDelta.y;
		// }

		// ImGui::SetCursorPos(imagePosition);
		// ImGui::Image((void*)(intptr_t)my_image_texture, imageSize);

		// ImGui::End();



		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Set window background color
		ImGui::Begin("OpenGL Texture Text", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::Text("Window Size: %.0f x %.0f", windowSize.x, windowSize.y);
		// ImVec2 mousePos = ImGui::GetMousePos(); // Get mouse position
		// ImVec2 windowPos = ImGui::GetWindowPos(); // Get window position

		// bool isMouseInsideWindow = mousePos.x >= windowPos.x && mousePos.x <= windowPos.x + windowSize.x &&
		// 							mousePos.y >= windowPos.y && mousePos.y <= windowPos.y + windowSize.y;


		static float scale = 1.0f; // Initial scale factor
		static ImVec2 imageOffset(0, 0); // Center image position
		ImGui::Text("scale = %f", scale);

		scale += ImGui::GetIO().MouseWheel * 0.1f;

		ImVec2 imageSize(my_image_width * scale, my_image_height * scale);

		ImVec2 imageOrigin(windowSize.x / 2.0f, windowSize.y / 2.0f); // Set origin to center of window

		ImVec2 imagePosition = ImVec2(imageSize.x / 2.0f, imageSize.y / 2.0f);
		imagePosition.x = imageOrigin.x - imagePosition.x;
		imagePosition.y = imageOrigin.y - imagePosition.y;

		if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
		{
			ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
			imageOffset.x += mouseDelta.x;
			imageOffset.y += mouseDelta.y;
		}

		imagePosition.x += imageOffset.x;
		imagePosition.y += imageOffset.y;
		ImGui::SetCursorPos(imagePosition);
		ImGui::Image((void*)(intptr_t)my_image_texture, imageSize);
		ImGui::End();
		ImGui::PopStyleColor();




		// ImGui::Begin("OpenGL Texture Text", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		// // static ImVec2 imagePosition(0.0f, 0.0f);
		// ImVec2 windowSize = ImGui::GetWindowSize();
		// ImGui::Text("Window Size: %.0f x %.0f", windowSize.x, windowSize.y);


		// static float scale = 1.0f; // Initial scale factor
		// // Adjust scale factor based on mouse scroll
		// scale += ImGui::GetIO().MouseWheel * 0.1f;

		// ImVec2 imageSize(my_image_width * scale, my_image_height * scale);

		// // static ImVec2 imagePosition(imageSize.x / -2.0f, imageSize.y / -2.0f); // Center image position
		// static ImVec2 imagePosition(0, 0); // Center image position

		// ImGui::Text("position = %f, %f", imagePosition.x, imagePosition.y);


		// if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
		// {
		// 	ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
		// 	imagePosition.x += mouseDelta.x;
		// 	imagePosition.y += mouseDelta.y;
		// }



		// ImGui::SetCursorPos(imagePosition);
		// ImGui::Image((void*)(intptr_t)my_image_texture, imageSize);

		// ImGui::End();



	


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