#pragma once

#include "../Test.h"


#include "FrameBuffer.h"

namespace tests
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;

		void OnRender() override;

		void OnImGuiRender() override;


	private:
		float m_ClearColor[4];
		bool m_VSync;

		// GLuint m_FBO;
		// GLuint m_FrameBufferTexture;
		// FrameBuffer* m_FrameBuffer;
		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		//imgui vec2
		ImVec2 m_ViewportSize;

		bool m_ViewPortFocused = false, m_ViewPortHovered = false;
	};
} // namespace Test