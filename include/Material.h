#pragma once

#include "Config.h"

class Material
{
public:
	Material(const std::string& file);
	~Material();
	void	use(int unit);

private:
	GLuint	m_Texture;
};