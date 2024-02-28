#pragma once

#include "Config.h"

// class TriangleMesh
// {
// public:
// 	TriangleMesh();
// 	void draw();
// 	~TriangleMesh();

// private:
// 	GLuint VBO, VAO, vertex_count;
// 	GLuint EBO;
// 	std::vector<GLuint> VBOs;
// };

class TriangleMesh {
public:
TriangleMesh();
void draw();
~TriangleMesh();

private:
GLuint EBO, VAO, element_count, RBO;
std::vector<unsigned int> VBOs;
};