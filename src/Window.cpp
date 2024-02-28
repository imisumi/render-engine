#include "Window.h"

#include "App.h"

// static void glfw_error_callback(int error, const char* description)
// {
// 	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
// }

// namespace Window
// {
// 	Window(uint32_t width, uint32_t height, const std::string& title)
// 		// : m_Width(width), m_Height(height), m_Title(title) // Add curly braces here
// 	{
// 		// glfwSetErrorCallback(glfw_error_callback);
// 		if (!glfwInit())
// 		{
// 			fprintf(stderr, "Failed to initialize GLFW\n");
// 		}
// 	}
// }



Window::Window(uint32_t width, uint32_t height, const std::string& title, bool vsync)
	: m_Width(width), m_Height(height), m_Title(title)
{
	// glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 3.0+ only

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(vsync); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	// Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);

	ImGui_ImplOpenGL3_Init("#version 460 core");

}



Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}


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


//update func
void	Window::Run()
{
	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
	// bool ret = LoadTextureFromFile("/home/imisumi/Desktop/render-engine/uv.png", &my_image_texture, &my_image_width, &my_image_height);
	bool ret = LoadTextureFromFile("C:/dev/render-engine/uv.png", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
	// Main loop
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//? My code

		ImGuiIO& io = ImGui::GetIO();

		// App::RenderUI();

		ImGui::Begin("fps");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		// ImGui::Begin("fps");
		// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		// ImGui::End();



		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Set window background color
		ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
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









		
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		//? End of my code
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);
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

		glfwSwapBuffers(m_Window);
	}
}