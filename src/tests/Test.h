#pragma once

#include "Renderer.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <functional>
#include <vector>

namespace tests
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu() = delete;
		TestMenu(Test*& currentTestPointer);
		// ~TestMenu();

		void OnImGuiRender() override ;

		Test* FindTest(const std::string& name)
		{
			for (auto& test : m_Tests)
			{
				if (test.first == name)
					return test.second();
			}
			return nullptr;
		}

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

	};

} // namespace Test
