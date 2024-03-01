#pragma once

#include "../Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"

#include <memory>

namespace tests
{
	class TestCamera : public Test
	{
	public:
		TestCamera();
		~TestCamera();

		void OnUpdate(float deltaTime) override;

		void OnRender() override;

		void OnImGuiRender() override;

	private:
		float m_ClearColor[4];
		bool m_VSync;

		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Projection;
		glm::mat4 m_View;

		glm::mat4 m_Model;


		float m_Rotation;
		float m_RotationSpeed;
		double m_PrevTime;

		Camera m_Camera;

	};
} // namespace Test