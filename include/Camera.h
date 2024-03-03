#pragma once

// #include "App.h"

#include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/type_ptr.hpp"
// // #include "glm"

// #include <GLFW/glfw3.h>

// #include "Window.h"


class Camera
{
public:

	// Camera() = delete;
	Camera();
	Camera(int width, int height, glm::vec3 position, glm::vec3 direction);
	~Camera();

	void	Movement(float deltaTIme);

	// void Matrix(float FOV, float aspectRatio, float near, float far);
	void SetPrespective(float FOV, float aspectRatio, float near, float far);

	void RecalculateView();

	glm::vec3 GetPos() const { return m_Position; }
	glm::vec3 GetDir() const { return m_Direction; }
	glm::vec3 GetUp() const { return m_Up; }
	glm::vec3 GetRot() const { return m_Rotation; }

	void	SetPos(glm::vec3 pos) { m_Position = pos; }
	// void	SetDir(glm::vec3 dir);
	void	SetUp(glm::vec3 up) { m_Up = up; }
	void	SetRot(glm::vec3 rot);

	void	SetWidth(int width) { m_Width = width; }
	void	SetHeight(int height) { m_Height = height; }

	int		GetWidth() const { return m_Width; }
	int		GetHeight() const { return m_Height; }


	glm::mat4 GetView() const { return m_View; }
	glm::mat4 GetProjection() const { return m_Projection; }


private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;

	glm::vec3 m_Rotation;

	float m_FOV;
	float m_AspectRatio;
	float m_Near;
	float m_Far;

	int m_Width;
	int m_Height;

	float m_Speed;

	float m_Sensitivity;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	bool m_FirstMouse;
	float m_Yaw;
	float m_Pitch;
	float m_LastX;

	float m_FirstClick = true;
};
