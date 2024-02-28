#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Camera
{
public:
	Camera(float verticalFOV, float nearClip, float farClip);

// 	// bool OnUpdate(float ts);
// 	// void OnResize(uint32_t width, uint32_t height);

// 	// const glm::mat4& GetProjection() const { return m_Projection; }
// 	// const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
// 	// const glm::mat4& GetView() const { return m_View; }
// 	// const glm::mat4& GetInverseView() const { return m_InverseView; }
	
// 	// const glm::vec3& GetPosition() const { return m_Position; }
// 	// const glm::vec3& GetDirection() const { return m_ForwardDirection; }

	void	RecalculateProjection();
	void	RecalculateView();


// 	// float GetRotationSpeed();

	void	SetPosition(const glm::vec3& position) { m_Position = position; }
	void	SetDirection(const glm::vec3& direction) { m_ForwardDirection = direction; }
	void	setUpDirection(const glm::vec3& up) { m_UpDirection = up; }

	void	setView(const glm::mat4& view) { m_View = view; }


	// glm::vec3	getPosition() { return m_Position; } const
	// return position as const function
	glm::vec3	getPosition() const { return m_Position; }
	glm::vec3	getDirection() const { return m_ForwardDirection; }
	glm::vec3	getUpDirection() const { return m_UpDirection; }

	const glm::mat4& GetProjection() const { return m_Projection; }
	const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
	const glm::mat4& GetView() const { return m_View; }


private:
	glm::mat4 m_Projection{ 1.0f };
	glm::mat4 m_View{ 1.0f };
	glm::mat4 m_InverseProjection{ 1.0f };
	glm::mat4 m_InverseView{ 1.0f };

	float m_VerticalFOV = 45.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;

	glm::vec3 m_Position{-5.0f, 0.0f, 3.0f};
	glm::vec3 m_ForwardDirection{1.0f, 0.0f, 0.0f};
	glm::vec3 m_UpDirection{0.0f, 0.0f, 1.0f};

// 	// Cached ray directions
// 	// std::vector<glm::vec3> m_RayDirections;

	glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };

	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
};
