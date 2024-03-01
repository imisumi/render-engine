#pragma once

#include "glm/glm.hpp"

class Camera
{
public:

	Camera();
	~Camera();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;

	float m_FOV;
	float m_AspectRatio;
	float m_Near;
	float m_Far;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	bool m_FirstMouse;
	float m_Yaw;
	float m_Pitch;
	float m_LastX;
};
