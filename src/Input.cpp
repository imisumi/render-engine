#include "App.h"

#include <GLFW/glfw3.h>

bool Input::IsKeyDown(int keycode)
{
	GLFWwindow* windowHandle = App::Get().GetWindowHandle();
	std::cout << "windowHandle: " << windowHandle << std::endl;
	int state = glfwGetKey(windowHandle, keycode);
	// return state == GLFW_PRESS || state == GLFW_REPEAT;
	return false;
}

// bool Input::IsMouseButtonDown(MouseButton button)
// {
// 	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
// 	int state = glfwGetMouseButton(windowHandle, (int)button);
// 	return state == GLFW_PRESS;
// }

// glm::vec2 Input::GetMousePosition()
// {
// 	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
// 	double x, y;
// 	glfwGetCursorPos(windowHandle, &x, &y);
// 	return { (float)x, (float)y };
// }

// void Input::SetCursorMode(CursorMode mode)
// {
// 	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
// 	glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
// }