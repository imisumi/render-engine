#pragma once

#include "tests/Test.h"
#include "tests/TestClearColor/TestClearColor.h"
#include "tests/TestTexture2D/TestTexture2D.h"
#include "tests/TestCamera/TestCamera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"

#include <iostream>

class App
{
public:
	App() = delete;
	App(int width, int height, const char* title);
	~App();

	void Run();

	void SetWindow(GLFWwindow* window) { m_WindowHandle = window; }
	GLFWwindow* GetWindow() const { return m_WindowHandle; }

private:
	GLFWwindow* m_WindowHandle;
	int m_Width;
	int m_Height;

	tests::Test* m_CurrentTest = nullptr;
	tests::TestMenu* m_TestMenu = nullptr;

	// float m_PrevFrameTime = 0.0f;
};
