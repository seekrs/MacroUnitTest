#include <Imgui/Panels/Docks.h>

namespace mlxut
{
	Docks::Docks() : Panel("docks") {}

	void Docks::OnUpdate(ivec2 size)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 4 + 1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 2, static_cast<float>(size.y) / 2.f + 1});
		if(ImGui::Begin("CentralDockSpaceWindow", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
		{
			ImGuiID dockspace_id = ImGui::GetID("CentralDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);

			static bool first_time_docks = true;
			if(first_time_docks)
			{
				ImGui::DockBuilderRemoveNode(dockspace_id);
				ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoWindowMenuButton);
				ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetWindowSize());

				ImGui::DockBuilderDockWindow("About", dockspace_id);
				ImGui::DockBuilderDockWindow("Render Results", dockspace_id);

				ImGui::DockBuilderFinish(dockspace_id);

				first_time_docks = false;
			}
			ImGui::End();
		}

		ImGui::PopStyleVar();
/////////////////////////////////////////////////////////////////////////////////////////////////
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });

		ImVec2 work_pos = ImVec2{ 0.f, m_main_menu_bar.GetHeight() };
		ImVec2 work_size = ImVec2{ size.x, size.y - m_main_menu_bar.GetHeight() };

		ImGui::SetNextWindowPos(work_pos);
		ImGui::SetNextWindowSize(work_size);
		if(ImGui::Begin("MainDockspaceWindow", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
		{
			if(ImGui::DockBuilderGetNode(ImGui::GetID("MainDockspace")) == nullptr)
			{
				ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
				ImGui::DockBuilderRemoveNode(dockspace_id);
				ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_NoWindowMenuButton);
				ImGui::DockBuilderSetNodeSize(dockspace_id, work_size);

				ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 1.f, nullptr, &dockspace_id);
				ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_left_id, ImGuiDir_Right, 0.85f, nullptr, &dock_left_id);
				ImGuiID dock_bottom_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Down, 0.2f, nullptr, &dock_right_id);

				ImGui::DockBuilderDockWindow(KBH_ICON_MD_VIEW_IN_AR" Parameters", dock_left_id);
				ImGui::DockBuilderDockWindow(KBH_ICON_MD_INFO" About", dock_right_id);
				ImGui::DockBuilderDockWindow(KBH_ICON_MD_MONITOR" Render", dock_right_id);
				ImGui::DockBuilderDockWindow(KBH_ICON_MD_SETTINGS" Settings", dock_right_id);
				ImGui::DockBuilderDockWindow(KBH_ICON_MD_TERMINAL" Logs", dock_bottom_id);

				ImGui::DockBuilderFinish(dockspace_id);
			}
			ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2{ 0.f, 0.f }, ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_NoWindowMenuButton);
			ImGui::End();
		}

		ImGui::PopStyleVar();
	}
}
