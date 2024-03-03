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

int main()
{
	App app(1600, 1200, "OpenGL");

	app.Run();

	return 0;
}
