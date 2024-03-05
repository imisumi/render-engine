#include "TestCamera.h"

// #include <GLFW/glfw3.h>

#include "App.h"

namespace tests
{
	TestCamera::TestCamera()
		: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{
		m_VSync = true;

		FrameBufferSpecification spec;
		spec.Width = 960;
		spec.Height = 541;

		// m_FrameBuffer = new FrameBuffer(spec);
		m_FrameBuffer = std::make_unique<FrameBuffer>(spec);

		m_ViewportSize = ImVec2{ 960, 540 };
		m_PrevViewportSize = ImVec2{ 960, 540 };



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


		m_Width = spec.Width;
		m_Height = spec.Height;
		m_Camera = Camera(m_Width, m_Height, glm::vec3(0.0f, 0.5f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	
		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 5 * 8 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 3 * 6);

		std::string vertexPath("../src/tests/TestCamera/vert.glsl");
		std::string fragmentPath ("../src/tests/TestCamera/frag.glsl");
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
		// m_FrameBuffer = std::make_unique<FrameBuffer>(spec);
	}

	TestCamera::~TestCamera()
	{
		GLCall(glDisable(GL_BLEND));
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void TestCamera::OnUpdate(float deltaTime)
	{
		if (m_ViewportSize.x != m_PrevViewportSize.x || m_ViewportSize.y != m_PrevViewportSize.y)
		{
			std::cout << "Resizing framebuffer: " << m_ViewportSize.x << ", " << m_ViewportSize.y << std::endl;
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_Camera.SetWidth((int)m_ViewportSize.x);
			m_Camera.SetHeight((int)m_ViewportSize.y);
			m_Camera.SetPrespective(45.0f, (float)m_Camera.GetWidth() / (float)m_Camera.GetHeight(), 0.1f, 100.0f);
			// GLCall(glViewport(0, 0, m_Camera.GetWidth(), m_Camera.GetHeight()));
		}


		m_Camera.Movement(deltaTime);
		m_Rotation += m_RotationSpeed * deltaTime;
		m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void TestCamera::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		// GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));



		m_FrameBuffer->Bind();
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		// GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


		// m_Camera.SetPrespective(45.0f, , 0.1f, 100.0f);
		m_Shader->SetUniformMat4f("u_Model", m_Model);
		m_Shader->SetUniformMat4f("u_View", m_Camera.GetView());
		m_Shader->SetUniformMat4f("u_Projection", m_Camera.GetProjection());



		m_Texture->Bind();





		Renderer renderer;
		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

		m_FrameBuffer->Unbind();
	}


	void TestCamera::OnImGuiRender()
	{
		ImGui::Checkbox("VSync", &m_VSync);
		glfwSwapInterval(m_VSync);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::ColorEdit4("Clear Color", m_ClearColor);


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		if (ImGui::Begin("Viewport"))
		{
			m_ViewPortFocused = ImGui::IsWindowFocused();
			m_ViewPortHovered = ImGui::IsWindowHovered();
			m_PrevViewportSize = m_ViewportSize;
			m_ViewportSize =ImGui::GetContentRegionAvail();
			ImVec2 imgSize = ImVec2{ (float)m_FrameBuffer->GetWidth(), (float)m_FrameBuffer->GetHeight() };
			// ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), imgSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::Image((void*)(intptr_t)m_FrameBuffer->GetColorAttachmentRendererID(), m_ViewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		}
		ImGui::End();
		ImGui::PopStyleVar();



		if (ImGui::Begin("Settings"))
		{
			ImGui::Text("Viewport Size: %.0f x %.0f", m_ViewportSize.x, m_ViewportSize.y);
			FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
			ImGui::Text("FrameBuffer Size: %d  %d", spec.Width, spec.Height);
			// focudes and hovered
			ImGui::Text("Viewport Focused: %d", m_ViewPortFocused);
			ImGui::Text("Viewport Hovered: %d", m_ViewPortHovered);
			ImGui::Text("Camera dimensions: %d x %d", m_Camera.GetWidth(), m_Camera.GetHeight());

			ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 250.0f);
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
		ImGui::End();
	}
} // namespace test

