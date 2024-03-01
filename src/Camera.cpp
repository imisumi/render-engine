#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 direction)
{
	// glm::mat4 view(1.0f);
	// m_Position = position;

	// m_View =  glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	m_Position = position;
	m_Direction = direction;
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_Width = width;
	m_Height = height;

}

Camera::~Camera()
{
}

void Camera::Movement(float deltaTIme)
{
	// GLFWwindow* window = Window::GetWindow();
// 	// m_Speed *= deltaTIme;
// 	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 	// 	m_Position += m_Speed * m_Direction;
// 	// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 	// 	m_Position -= m_Speed * m_Direction;
// 	// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 	// 	m_Position -= glm::normalize(glm::cross(m_Direction, m_Up)) * m_Speed;
// 	// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 	// 	m_Position += glm::normalize(glm::cross(m_Direction, m_Up)) * m_Speed;
}

void Camera::Matrix(float FOV, float aspectRatio, float near, float far)
{
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	m_Projection = glm::perspective(glm::radians(FOV), (float)(m_Width / m_Height), near, far);
}

void Camera::SetPrespective(float FOV, float aspectRatio, float near, float far)
{
	m_Projection = glm::perspective(glm::radians(FOV), aspectRatio, near, far);
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}
