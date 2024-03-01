#pragma once

#include "../Test.h"

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
	};
} // namespace Test