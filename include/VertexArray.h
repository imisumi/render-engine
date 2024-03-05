#pragma once

#include "VertexBuffer.h"
// #include "VertexBufferLayout.h"

class VertexBufferLayout;

// #include <glad/glad.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	// void AddBuffer(const VertexBuffer& vb, GLuint index);
	void Bind() const;
	void Unbind() const;

private:
	GLuint m_RendererID;

};
