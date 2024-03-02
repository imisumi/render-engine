#include "TestClearColor.h"

// #include <GLFW/glfw3.h>

namespace tests
{
	TestClearColor::TestClearColor()
		: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{
		m_VSync = true;
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::Checkbox("VSync", &m_VSync);
		glfwSwapInterval(m_VSync);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
} // namespace test
