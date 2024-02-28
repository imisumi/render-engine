#pragma once

#include "Config.h"

#include "Scene.h"

class App
{
public:
	App();
	~App();

	static App& Get();

	void Run();

	// void OnUpdate(float ts);
	// void OnRender();
	// void OnEvent();
	// void OnResize(int width, int height);

	void SetTimeStep(float timeStep) { m_TimeStep = timeStep; }
	float GetTimeStep() const { return m_TimeStep; }

	void SetFrameTime(float frameTime) { m_FrameTime = frameTime; }
	float GetFrameTime() const { return m_FrameTime; }

	void SetLastFrameTime(float lastFrameTime) { m_LastFrameTime = lastFrameTime; }
	float GetLastFrameTime() const { return m_LastFrameTime; }

	GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

private:
	void Init();
	void Shutdown();

	void OnInput();

private:
	GLFWwindow* m_WindowHandle = nullptr;
	int	m_Width = 1200;
	int	m_Height = 1200;

	float m_TimeStep = 0.0f;
	float m_FrameTime = 0.0f;
	float m_LastFrameTime = 0.0f;

	bool m_vSync = false;

	// vector of Scenes
	// std::vector<Scene*> m_Scenes{0};
	Scene* m_Scene = nullptr;

	Shader m_Shader;

	//temp
	GLuint m_Program;

	GLuint m_Texture;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_ShaderProgram;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_Texture1;
	GLuint m_Texture2;

	Material* m_Material = nullptr;

	glm::vec3 m_QuadPos;
	GLuint m_ModelLoc;
};


