#pragma once

#include "Config.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Draw();

	std::vector<GLuint> m_Textures;
};