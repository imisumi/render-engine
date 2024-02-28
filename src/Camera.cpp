#include "Camera.h"

Camera::Camera(float verticalFOV, float nearClip, float farClip)
{
	m_VerticalFOV = verticalFOV;
	m_NearClip = nearClip;
	m_FarClip = farClip; 


	m_ForwardDirection = glm::vec3(0, 0, -1);
	m_Position = glm::vec3(0, 0, 6);
}

// bool Camera::OnUpdate(float ts)
// {
// 	glm::vec2 mousePos = Input::GetMousePosition();
// 	glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.002f;
// 	m_LastMousePosition = mousePos;

// 	if (!Input::IsMouseButtonDown(MouseButton::Right))
// 	{
// 		Input::SetCursorMode(CursorMode::Normal);
// 		return false;
// 	}

// 	Input::SetCursorMode(CursorMode::Locked);

// 	bool moved = false;

// 	constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
// 	glm::vec3 rightDirection = glm::cross(m_ForwardDirection, upDirection);

// 	float speed = 5.0f;

// 	// Movement
// 	// glfwGetKey(window, GLFW_KEY_W);
// 	if (Input::IsKeyDown(KeyCode::W))
// 	{
// 		m_Position += m_ForwardDirection * speed * ts;
// 		moved = true;
// 	}
// 	else if (Input::IsKeyDown(KeyCode::S))
// 	{
// 		m_Position -= m_ForwardDirection * speed * ts;
// 		moved = true;
// 	}
// 	if (Input::IsKeyDown(KeyCode::A))
// 	{
// 		m_Position -= rightDirection * speed * ts;
// 		moved = true;
// 	}
// 	else if (Input::IsKeyDown(KeyCode::D))
// 	{
// 		m_Position += rightDirection * speed * ts;
// 		moved = true;
// 	}
// 	if (Input::IsKeyDown(KeyCode::Q))
// 	{
// 		m_Position -= upDirection * speed * ts;
// 		moved = true;
// 	}
// 	else if (Input::IsKeyDown(KeyCode::E))
// 	{
// 		m_Position += upDirection * speed * ts;
// 		moved = true;
// 	}

// 	// Rotation
// 	if (delta.x != 0.0f || delta.y != 0.0f)
// 	{
// 		float pitchDelta = delta.y * GetRotationSpeed();
// 		float yawDelta = delta.x * GetRotationSpeed();

// 		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
// 			glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
// 		m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

// 		moved = true;
// 	}

// 	if (moved)
// 	{
// 		RecalculateView();
// 		RecalculateRayDirections();
// 	}

// 	return moved;
// }

// void Camera::OnResize(uint32_t width, uint32_t height)
// {
// 	if (width == m_ViewportWidth && height == m_ViewportHeight)
// 		return;

// 	m_ViewportWidth = width;
// 	m_ViewportHeight = height;

// 	RecalculateProjection();
// 	RecalculateRayDirections();
// }

// float Camera::GetRotationSpeed()
// {
// 	return 0.3f;
// }

void Camera::RecalculateProjection()
{
	m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
	m_InverseProjection = glm::inverse(m_Projection);
}

void Camera::RecalculateView()
{
	// m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, m_UpDirection);
	m_View = glm::lookAt(m_Position, m_ForwardDirection, m_UpDirection);
	m_InverseView = glm::inverse(m_View);
}
