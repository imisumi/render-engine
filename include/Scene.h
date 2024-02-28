#pragma once

#include "Camera.h"

class Scene
{
public:
	Scene();
	~Scene();

	// void OnUpdate(float ts);
	// void OnRender();
	// void OnEvent();
	// void OnResize(int width, int height);

	Camera m_Camera;
};

