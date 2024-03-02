#include "Camera.h"
#include "App.h"

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>



// class App;

// App& GetApp();


Camera::Camera()
{
}

Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 direction)
{
	// glm::mat4 view(1.0f);
	// m_Position = position;

	// m_View =  glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	m_Position = position;
	m_Direction = glm::normalize(direction);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	m_Width = width;
	m_Height = height;

	m_Speed = 2.0f;
	m_Sensitivity = 10000.0f;

	float pitch = glm::degrees(asinf(-direction.y)); // Calculate pitch angle (rotation around x-axis)
	float yaw = glm::degrees(atan2f(direction.x, direction.z)); // Calculate yaw angle (rotation around y-axis)

	// Convert yaw angle to range [0, 360]
	if (yaw < 0)
		yaw += 360.0f;
	m_Rotation = glm::vec3(pitch, yaw, 0.0f);

}

Camera::~Camera()
{
}

void Camera::Movement(float deltaTime)
{
	// std::cout << "Camera::Movement" << std::endl;
	// GLFWwindow* window = Window::GetWindow();
	GLFWwindow* window = App::Get().GetWindowHandle();
	float speed = m_Speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		std::cout << "Space" << std::endl;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position += speed * m_Direction;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position -= speed * m_Direction;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= glm::normalize(glm::cross(m_Direction, m_Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += glm::normalize(glm::cross(m_Direction, m_Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_Position -= m_Up * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_Position += m_Up * speed;



	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// std::cout << "Right Mouse Button" << std::endl;
		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		float sensitivity = m_Sensitivity * deltaTime;

		if (m_FirstClick)
		{
			glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
			m_FirstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (m_Height / 2)) / m_Height;
		float rotY = sensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;

		glm::vec3 newOrientation = glm::rotate(m_Direction, glm::radians(-rotX), glm::normalize(glm::cross(m_Direction, m_Up)));

		if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_Direction = newOrientation;
		}

		m_Direction = glm::rotate(m_Direction, glm::radians(-rotY), m_Up);

		glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_FirstClick = true;
	}


	RecalculateView();
}

void Camera::RecalculateView()
{
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
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


void	Camera::SetRot(glm::vec3 rot)
{
	// m_Rotation = rot;
	// m_Direction.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
	// m_Direction.y = sin(glm::radians(m_Rotation.x));
	// m_Direction.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
	// m_Direction = glm::normalize(m_Direction);
	// RecalculateView();
}


// void	Camera::SetDir(glm::vec3 dir)
// {
// 	m_Direction = dir;
// 	RecalculateView();
// }

void Camera::SetDir(glm::vec3 dir)
{
    m_Direction = dir;

    // Calculate pitch (rotation around the x-axis)
    float pitch = glm::degrees(asinf(-dir.y));

    // Calculate yaw (rotation around the y-axis)
    float yaw = glm::degrees(atan2f(dir.x, dir.z));

    // Roll (rotation around the z-axis) can be derived from the direction vector,
    // but it's generally not meaningful for a camera orientation, as it can cause
    // undesirable behavior (e.g., camera flipping). You may set it to a default value
    // or leave it as-is.

    // Set the rotations
    // SetRot(glm::vec3(pitch, yaw, 0.0f));
	m_Rotation = glm::vec3(pitch, yaw, 0.0f);
	// m_Rotation = glm::vec3(1.0, 1.0f, 0.0f);
	// std::cout << "Rotation: " << m_Rotation.x << " " << m_Rotation.y << " " << m_Rotation.z << std::endl;
    RecalculateView();
}