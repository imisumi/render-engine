#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <iostream>


class Window
{
public:
	Window(uint32_t width, uint32_t height, const std::string& title, bool vsync);
	~Window();

	void Run();


private:
	GLFWwindow*	m_Window;
	uint32_t	m_Width;
	uint32_t	m_Height;
	std::string	m_Title;

	// ImGuiIO&	m_io;
	// ImGuiIO& m_io = ImGui::GetIO();
};
