#include "TestCamera.h"

// #include <GLFW/glfw3.h>

namespace tests
{
	TestCamera::TestCamera()
		: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{
		m_VSync = true;

		FrameBufferSpecification spec;
		spec.Width = 960;
		spec.Height = 541;

		// m_FrameBuffer = new FrameBuffer(spec);
		m_FrameBuffer = std::make_unique<FrameBuffer>(spec);

		m_ViewportSize = ImVec2{ 960, 540 };
	}

	TestCamera::~TestCamera()
	{
	}

	void TestCamera::OnUpdate(float deltaTime)
	{
		m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	void TestCamera::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));


		m_FrameBuffer->Bind();

		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_FrameBuffer->Unbind();
	}


	void TestCamera::OnImGuiRender()
	{
		ImGui::Checkbox("VSync", &m_VSync);
		glfwSwapInterval(m_VSync);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::ColorEdit4("Clear Color", m_ClearColor);


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		m_ViewPortFocused = ImGui::IsWindowFocused();
		m_ViewPortHovered = ImGui::IsWindowHovered();
		m_ViewportSize =ImGui::GetContentRegionAvail();
		ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), ImVec2{ (float)m_FrameBuffer->GetWidth(), (float)m_FrameBuffer->GetHeight() });
		ImGui::End();
		ImGui::PopStyleVar();



		ImGui::Begin("Settings");
		ImGui::Text("Window Size: %.0f x %.0f", m_ViewportSize.x, m_ViewportSize.y);
		FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
		ImGui::Text("FrameBuffer Size: %d  %d", spec.Width, spec.Height);
		// focudes and hovered
		ImGui::Text("Viewport Focused: %d", m_ViewPortFocused);
		ImGui::Text("Viewport Hovered: %d", m_ViewPortHovered);
		ImGui::End();

	}
} // namespace test
