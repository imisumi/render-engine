#pragma once

#include "tests/Test.h"


#include <iostream>

class App
{
public:
	App() = delete;
	App(int width, int height, const char* title);
	~App();

	static App& Get();

	void Run();

	void SetWindow(GLFWwindow* window) { m_WindowHandle = window; }
	GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

private:
	GLFWwindow* m_WindowHandle;
	int m_Width;
	int m_Height;

	tests::Test* m_CurrentTest = nullptr;
	tests::TestMenu* m_TestMenu = nullptr;

	// float m_PrevFrameTime = 0.0f;
};
