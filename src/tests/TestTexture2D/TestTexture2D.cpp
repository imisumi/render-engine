#include "TestTexture2D.h"

// #include <GLFW/glfw3.h>

namespace tests
{
	TestTexture2D::TestTexture2D()
		: m_VSync(true), m_TranslationA(100.0f, 100.0f, 0.0f), m_TranslationB(200.0f, 200.0f, 0.0f),
		m_Proj(glm::ortho(0.0f, 1600.0f, 0.0f, 1200.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
		100.0f, 100.0f, 0.0f, 0.0f,
		200.0f, 100.0f, 1.0f, 0.0f,
		200.0f, 200.0f, 1.0f, 1.0f,
		100.0f, 200.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		std::string vertexPath("../shaders/default.vert");
		std::string fragmentPath ("../shaders/default.frag");
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
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));


		Renderer renderer;

		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Checkbox("VSync", &m_VSync);
		glfwSwapInterval(m_VSync);
		// ImGui::ColorEdit4("Clear Color", m_ClearColor);

		ImGui::SliderFloat3("Translation A", glm::value_ptr(m_TranslationA), 0.0f, 1600.0f);
		ImGui::SliderFloat3("Translation B", glm::value_ptr(m_TranslationB), 0.0f, 1600.0f);
	}
} // namespace test
