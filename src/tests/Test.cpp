#include "Test.h"

namespace tests
{
	// TestMenu::TestMenu()
	// 	: m_CurrentTest(nullptr)
	// {
	// }

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{
	}

	// TestMenu::~TestMenu()
	// {
	// }

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				std::cout << "Switching to " << test.first << std::endl;
				m_CurrentTest = test.second();
			}
		}
	}
}