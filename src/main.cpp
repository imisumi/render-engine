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


// static App* s_AppInstance = nullptr;

int main()
{
	App app(1600, 1200, "OpenGL");

	app.Run();

	return 0;
}
