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
	// m_Sensitivity = 10000.0f;
	m_Sensitivity = 30.0f;

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


glm::vec3 CalculateDirectionFromEulerAngles(const glm::vec3& rotation)
{
	// Convert Euler angles from degrees to radians
	glm::vec3 rotationRadians = glm::radians(rotation);

	// Initialize a forward direction vector
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f); // Default forward direction

	// Apply rotations around X, Y, and Z axes in order
	direction = glm::rotateX(direction, -rotationRadians.x);
	direction = glm::rotateY(direction, -rotationRadians.y);
	direction = glm::rotateZ(direction, rotationRadians.z);

	// Return the resulting normalized direction vector
	return glm::normalize(direction);
}

void Camera::Movement(float deltaTime)
{
	GLFWwindow* window = App::Get().GetWindowHandle();
	float speed = m_Speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position += speed * m_Direction;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position -= speed * m_Direction;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position += glm::normalize(glm::cross(m_Direction, m_Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position -= glm::normalize(glm::cross(m_Direction, m_Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_Position -= m_Up * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_Position += m_Up * speed;



	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (m_FirstClick)
		{
			glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
			m_FirstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//TODO: Roll
		float pan = m_Sensitivity * deltaTime * (float)(mouseX - (m_Width / 2));
		float tilt = m_Sensitivity * deltaTime * (float)(mouseY - (m_Height / 2));

		m_Rotation.x += -tilt;
		m_Rotation.y += pan;

		m_Direction = CalculateDirectionFromEulerAngles(m_Rotation);

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

void Camera::SetPrespective(float FOV, float aspectRatio, float near, float far)
{
	m_Projection = glm::perspective(glm::radians(FOV), aspectRatio, near, far);
	glm::vec3 position = m_Position;
	position.x = -m_Position.x;
	m_View = glm::lookAt(position, position + m_Direction, m_Up);
}

void	Camera::SetRot(glm::vec3 rot)
{
	m_Rotation = rot;
	m_Direction = CalculateDirectionFromEulerAngles(m_Rotation);
	RecalculateView();
}

