

// #include <glad/glad.h> // Initialize with gladLoadGL()


// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include <stdio.h>
// // #define GL_SILENCE_DEPRECATION


// #include <GLFW/glfw3.h> // Will drag system OpenGL headers

// // [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// // To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// // Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
// // #if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
// // #pragma comment(lib, "legacy_stdio_definitions")
// // #endif

// // #include "Application.h"

// #include <iostream>
// #include "App.h"

// // Main code
// int main(int, char**)
// {
// 	// window unique_ptr
// 	// std::unique_ptr<Window> window = std::make_unique<Window>(1600, 1200, "Dear ImGui GLFW+OpenGL3 example", true);
// 	// window->Run();


// 	Window* windoww = new Window(1600, 1200, "Dear ImGui GLFW+OpenGL3 example", false);
// 	windoww->Run();
// 	return 0;


// 	glfwSetErrorCallback(glfw_error_callback);
// 	if (!glfwInit())
// 		return 1;

// 	// GL 3.0 + GLSL 130
// 	const char* glsl_version = "#version 130";
// 	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// 3.2+ only
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 3.0+ only

// 	// Create window with graphics context
// 	GLFWwindow* window = glfwCreateWindow(1600, 1200, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
// 	if (window == nullptr)
// 		return 1;
	
// 	glfwMakeContextCurrent(window);
// 	glfwSwapInterval(1); // Enable vsync

// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
// 	{
// 		std::cout << "Failed to initialize GLAD" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}



// 	// Setup Dear ImGui context
// 	IMGUI_CHECKVERSION();
// 	ImGui::CreateContext();
// 	ImGuiIO& io = ImGui::GetIO(); (void)io;
// 	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	 // Enable Keyboard Controls
// 	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	  // Enable Gamepad Controls
// 	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		 // Enable Docking
// 	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	   // Enable Multi-Viewport / Platform Windows
// 	//io.ConfigViewportsNoAutoMerge = true;
// 	//io.ConfigViewportsNoTaskBarIcon = true;

// 	// Setup Dear ImGui style
// 	ImGui::StyleColorsDark();
// 	//ImGui::StyleColorsLight();

// 	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
// 	ImGuiStyle& style = ImGui::GetStyle();
// 	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
// 	{
// 		style.WindowRounding = 0.0f;
// 		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
// 	}

// 	// Setup Platform/Renderer backends
// 	ImGui_ImplGlfw_InitForOpenGL(window, true);

// 	ImGui_ImplOpenGL3_Init(glsl_version);

// 	// Our state
// 	bool show_demo_window = true;
// 	bool show_another_window = false;
// 	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// 	// glfw disable vsync
// 	glfwSwapInterval(1);

// 	// Main loop
// 	while (!glfwWindowShouldClose(window))
// 	{

// 		glfwPollEvents();

// 		// Start the Dear ImGui frame
// 		ImGui_ImplOpenGL3_NewFrame();
// 		ImGui_ImplGlfw_NewFrame();
// 		ImGui::NewFrame();

// 		// if (show_demo_window)
// 		// 	ImGui::ShowDemoWindow(&show_demo_window);

// 		//? My code goes here
// 		// ImGui::Begin("Settings");
// 		// ImGui::Button("Hello");
// 		// ImGui::End();


// 		App::RenderUI();

// 		ImGui::Begin("fps");
// 		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
// 		ImGui::End();



// 		// Rendering
// 		ImGui::Render();
// 		int display_w, display_h;
// 		glfwGetFramebufferSize(window, &display_w, &display_h);
// 		glViewport(0, 0, display_w, display_h);
// 		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
// 		glClear(GL_COLOR_BUFFER_BIT);
// 		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

// 		// Update and Render additional Platform Windows
// 		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
// 		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
// 		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
// 		{
// 			GLFWwindow* backup_current_context = glfwGetCurrentContext();
// 			ImGui::UpdatePlatformWindows();
// 			ImGui::RenderPlatformWindowsDefault();
// 			glfwMakeContextCurrent(backup_current_context);
// 		}

// 		glfwSwapBuffers(window);
// 	}

// 	// Cleanup
// 	ImGui_ImplOpenGL3_Shutdown();
// 	ImGui_ImplGlfw_Shutdown();
// 	ImGui::DestroyContext();

// 	glfwDestroyWindow(window);
// 	glfwTerminate();

// 	return 0;
// }


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 1024;

const unsigned short OPENGL_MAJOR_VERSION = 4;
const unsigned short OPENGL_MINOR_VERSION = 6;

bool vSync = true;



GLfloat vertices[] =
{
	-1.0f, -1.0f , 0.0f, 0.0f, 0.0f,
	-1.0f,  1.0f , 0.0f, 0.0f, 1.0f,
	 1.0f,  1.0f , 0.0f, 1.0f, 1.0f,
	 1.0f, -1.0f , 0.0f, 1.0f, 0.0f,
};

GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2
};


const char* screenVertexShaderSource = R"(#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvs;
out vec2 UVs;
void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	UVs = uvs;
})";
const char* screenFragmentShaderSource = R"(#version 460 core
out vec4 FragColor;
uniform sampler2D screen;
in vec2 UVs;
void main()
{
	FragColor = texture(screen, UVs);
})";

// const char* screenComputeShaderSource = R"(#version 460 core
// layout(local_size_x = 8, local_size_y = 4, local_size_z = 1) in;
// layout(rgba32f, binding = 0) uniform image2D screen;
// void main()
// {
// 	vec4 pixel = vec4(0.075, 0.133, 0.173, 1.0);
// 	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	
// 	ivec2 dims = imageSize(screen);
// 	float x = -(float(pixel_coords.x * 2 - dims.x) / dims.x); // transforms to [-1.0, 1.0]
// 	float y = -(float(pixel_coords.y * 2 - dims.y) / dims.y); // transforms to [-1.0, 1.0]

// 	float fov = 90.0;
// 	vec3 cam_o = vec3(0.0, 0.0, -tan(fov / 2.0));
// 	vec3 ray_o = vec3(x, y, 0.0);
// 	vec3 ray_d = normalize(ray_o - cam_o);

// 	vec3 sphere_c = vec3(0.0, 0.0, -5.0);
// 	float sphere_r = 1.0;

// 	vec3 o_c = ray_o - sphere_c;
// 	float b = dot(ray_d, o_c);
// 	float c = dot(o_c, o_c) - sphere_r * sphere_r;
// 	float intersectionState = b * b - c;
// 	vec3 intersection = ray_o + ray_d * (-b + sqrt(b * b - c));

// 	if (intersectionState >= 0.0)
// 	{
// 		pixel = vec4((normalize(intersection - sphere_c) + 1.0) / 2.0, 1.0);
// 	}

// 	imageStore(screen, pixel_coords, pixel);
// })";

const char* screenComputeShaderSource = R"(#version 460 core
layout(local_size_x = 8, local_size_y = 4, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D screen;
void main()
{
	vec4 pixel = vec4(0.075, 0.133, 0.173, 1.0);
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	
	ivec2 dims = imageSize(screen);
	float x = -(float(pixel_coords.x * 2 - dims.x) / dims.x); // transforms to [-1.0, 1.0]
	float y = -(float(pixel_coords.y * 2 - dims.y) / dims.y); // transforms to [-1.0, 1.0]

	vec2 uv = pixel_coords / vec2(dims);

	imageStore(screen, pixel_coords, vec4(x, y, 0.0, 1.0));
	imageStore(screen, pixel_coords, vec4(uv, 0.0, 1.0));
})";


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Compute Shaders", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create the GLFW window\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vSync);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	GLuint VAO, VBO, EBO;
	glCreateVertexArrays(1, &VAO);
	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &EBO);

	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glEnableVertexArrayAttrib(VAO, 1);
	glVertexArrayAttribBinding(VAO, 1, 0);
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 5 * sizeof(GLfloat));
	glVertexArrayElementBuffer(VAO, EBO);


	GLuint screenTex;
	glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
	glTextureParameteri(screenTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(screenTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(screenTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(screenTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureStorage2D(screenTex, 1, GL_RGBA32F, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindImageTexture(0, screenTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	GLuint screenVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(screenVertexShader, 1, &screenVertexShaderSource, NULL);
	glCompileShader(screenVertexShader);
	GLuint screenFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(screenFragmentShader, 1, &screenFragmentShaderSource, NULL);
	glCompileShader(screenFragmentShader);

	GLuint screenShaderProgram = glCreateProgram();
	glAttachShader(screenShaderProgram, screenVertexShader);
	glAttachShader(screenShaderProgram, screenFragmentShader);
	glLinkProgram(screenShaderProgram);

	glDeleteShader(screenVertexShader);
	glDeleteShader(screenFragmentShader);


	GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeShader, 1, &screenComputeShaderSource, NULL);
	glCompileShader(computeShader);

	GLuint computeProgram = glCreateProgram();
	glAttachShader(computeProgram, computeShader);
	glLinkProgram(computeProgram);


	int work_grp_cnt[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);
	std::cout << "Max work groups per compute shader" << 
		" x:" << work_grp_cnt[0] <<
		" y:" << work_grp_cnt[1] <<
		" z:" << work_grp_cnt[2] << "\n";

	int work_grp_size[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
	std::cout << "Max work group sizes" <<
		" x:" << work_grp_size[0] <<
		" y:" << work_grp_size[1] <<
		" z:" << work_grp_size[2] << "\n";

	int work_grp_inv;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
	std::cout << "Max invocations count per work group: " << work_grp_inv << "\n";


	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		if (width != SCREEN_WIDTH || height != SCREEN_HEIGHT)
		{
			// Update the viewport size
			SCREEN_WIDTH = width;
			SCREEN_HEIGHT = height;
			glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			// Recreate any OpenGL resources dependent on window size
			glDeleteTextures(1, &screenTex);
			glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
			glTextureParameteri(screenTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(screenTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(screenTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(screenTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureStorage2D(screenTex, 1, GL_RGBA32F, SCREEN_WIDTH, SCREEN_HEIGHT);
			glBindImageTexture(0, screenTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
		}



		glUseProgram(computeProgram);
		// glDispatchCompute(ceil(SCREEN_WIDTH / 8), ceil(SCREEN_HEIGHT / 4), 1);
		glDispatchCompute((SCREEN_WIDTH + 7) / 8, (SCREEN_HEIGHT + 4) / 4, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);

		glUseProgram(screenShaderProgram);
		glBindTextureUnit(0, screenTex);
		glUniform1i(glGetUniformLocation(screenShaderProgram, "screen"), 0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
}