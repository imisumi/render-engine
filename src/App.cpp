#include "App.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <iostream>


namespace App
{
	void Run()
	{
		// This is the main function of the application
		std::cout << "Hello, World!" << std::endl;

	}

	void	RenderUI()
	{
		static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", nullptr, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
			if (ImGui::MenuItem("Flag: NoDockingSplit",		 "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0))			 { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
			if (ImGui::MenuItem("Flag: NoUndocking",			"", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0))				{ dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
			if (ImGui::MenuItem("Flag: NoResize",			   "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))				   { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar",		 "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))			 { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode",	"", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();

			ImGui::EndMenu();
		}
		// HelpMarker(
		//	 "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
		//	 "- Drag from window title bar or their tab to dock/undock." "\n"
		//	 "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
		//	 "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
		//	 "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
		//	 "This demo app has nothing to do with enabling docking!" "\n\n"
		//	 "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
		//	 "Read comments in ShowExampleAppDockSpace() for more details.");

		ImGui::EndMenuBar();
	}

		static ImVec4 backgroundColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//rgba format
		static float buffer[4 * 16] = { 1.0f };

		ImGui::Begin("Settings");
		ImGui::Button("Hello");
		ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);

		ImGui::End();


		ImGui::Begin("Viewport");


		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::GetWindowDrawList()->AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), ImGui::ColorConvertFloat4ToU32(ImVec4(buffer[0], buffer[1], buffer[2], buffer[3])));

		// ImGui::Image((void*)1, ImVec2(200, 200));
		// ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowSize(), ImGui::ColorConvertFloat4ToU32(backgroundColor));

		ImGui::End();







		ImGui::End();
	}
} // namespace App