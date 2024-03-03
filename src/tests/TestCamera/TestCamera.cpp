#include "TestCamera.h"

#include "App.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

// #include "App.h"

namespace tests
{
	TestCamera::TestCamera()
		: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }, m_VSync(true)
	{
		GLfloat vertices[] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
			-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
			0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,
			0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f,
			0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,		2.5f, 5.0f
		};

		// Indices for vertices order
		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4
		};

		// int width = App::Get().GetWidth();
		// int height = App::Get().GetHeight();

		m_Width = App::Get().GetWidth();
		m_Height = App::Get().GetHeight();
		m_Camera = Camera(m_Width, m_Height, glm::vec3(0.0f, 0.5f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		// m_Projection = glm::perspective(glm::radians(45.0f), 1600.0f / 1200.0f, 0.1f, 100.0f);
		// m_Model = glm::mat4(1.0f);

		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 5 * 8 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 3 * 6);

		std::string vertexPath("../shaders/tests/TestCamera/default.vert");
		std::string fragmentPath ("../shaders/tests/TestCamera/default.frag");
		#ifdef _WIN32
			vertexPath.insert(0, "../");
			fragmentPath.insert(0, "../");
		#endif

		m_Shader = std::make_unique<Shader>(vertexPath, fragmentPath);
		m_Shader->Bind();


		std::string texturePath("../uv.png");
		#ifdef _WIN32
			texturePath.insert(0, "../");
		#endif
		m_Texture = std::make_unique<Texture>(texturePath);
		m_Shader->SetUniform1i("u_Texture", 0);




		m_Rotation = 0.0f;
		m_PrevTime = 0.0;
		m_RotationSpeed = 125.0f;

		m_Camera.SetPrespective(45.0f, (float)m_Width / (float)m_Height, 0.1f, 100.0f);

		// Disable window size limits to allow resizing
		glfwSetWindowSizeLimits(App::Get().GetWindowHandle(), GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);

	}

	TestCamera::~TestCamera()
	{
		// GLCall(glEnable(GL_BLEND));
		// GLCall(glEnable(GL_DEPTH_TEST));
		// GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCall(glDisable(GL_BLEND));
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void TestCamera::OnResize()
	{
		GLFWwindow* window = App::Get().GetWindowHandle();
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		if (m_Camera.GetWidth() != width || m_Camera.GetHeight() != height)
		{
			m_Camera.SetWidth(width);
			m_Camera.SetHeight(height);
			m_Camera.SetPrespective(45.0f, (float)m_Camera.GetWidth() / (float)m_Camera.GetHeight(), 0.1f, 100.0f);
			GLCall(glViewport(0, 0, width, height));
		}
	}

	void TestCamera::OnUpdate(float deltaTime)
	{

		OnResize();
		// glfw get width and height
		// int width, height;
		// glfwGetWindowSize(App::Get().GetWindowHandle(), &width, &height);
		// if (width != m_Camera.GetWidth() || height != m_Camera.GetHeight())
		// {
		// 	m_Camera.SetWidth(width);
		// 	m_Camera.SetHeight(height);
		// 	m_Camera.SetPrespective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
		// }

		//on resize



		// m_Camera.SetDir(m_Camera.GetDir());
		m_Camera.Movement(deltaTime);
		m_Rotation += m_RotationSpeed * deltaTime;
		m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void TestCamera::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


		// glfw get width and height
		int width, height;
		glfwGetWindowSize(App::Get().GetWindowHandle(), &width, &height);
		m_Camera.SetPrespective(45.0f, (float)width / (float)height, 0.1f, 100.0f);


		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);


		// m_Camera.SetPrespective(45.0f, 1600.0f / 1200.0f, 0.1f, 100.0f);

		Renderer renderer;
		m_Texture->Bind();

		m_Shader->SetUniformMat4f("u_Model", m_Model);
		m_Shader->SetUniformMat4f("u_View", m_Camera.GetView());
		m_Shader->SetUniformMat4f("u_Projection", m_Camera.GetProjection());

		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);


		// {
		// 	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		// 	glm::mat4 mvp = m_Proj * m_View * model;
		// 	m_Shader->SetUniformMat4f("u_MVP", mvp);
		// 	renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		// }

		// {
		// 	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		// 	glm::mat4 mvp = m_Proj * m_View * model;
		// 	m_Shader->SetUniformMat4f("u_MVP", mvp);
		// 	renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		// }
	}

	void TestCamera::OnImGuiRender()
	{
		ImGui::Checkbox("VSync", &m_VSync);
		glfwSwapInterval(m_VSync);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		// ImGui::Text
		// float slider m_RotationSpeed 0 - 10
		ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 250.0f);


		// glm::vec3 camDiraction = m_Camera.GetDir();
		// camDiraction = glm::normalize(camDiraction);
		// ImGui::Text("Camera Direction:");
		// ImGui::Text("X: %.2f Y: %.2f Z: %.2f", camDiraction.x, camDiraction.y, camDiraction.z);

		glm::vec3 camPosition = m_Camera.GetPos();
		ImGui::Text("Camera Position:");
		ImGui::SameLine();
		if (ImGui::DragFloat3("##camPosition", glm::value_ptr(camPosition), \
			0.01f, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max(), "%.2f"))
		{
			m_Camera.SetPos(camPosition);
		}


		glm::vec3 camRotation = m_Camera.GetRot();
		ImGui::Text("Camera Rotation:");
		ImGui::SameLine();
		if (ImGui::DragFloat3("##camRotation", glm::value_ptr(camRotation), \
			1.0f, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max(), "%.2f"))
		{
			//TODO: Fix tils
			camRotation.z = 0.0f;
			m_Camera.SetRot(camRotation);
		}


	}
} // namespace test
