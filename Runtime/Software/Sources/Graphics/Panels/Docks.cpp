#include <Graphics/Panels/Docks.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	Docks::Docks(const MenuBar& menu_bar) : Panel("Docks"), m_menubar(menu_bar) {}

	void Docks::OnUpdate(ImVec2 size)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });

		ImVec2 work_pos = ImVec2{ 0.f, m_menubar.GetHeight() };
		ImVec2 work_size = ImVec2{ size.x, size.y - m_menubar.GetHeight() };

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
				ImGuiID dock_center_id = ImGui::DockBuilderSplitNode(dock_left_id, ImGuiDir_Right, 0.85f, nullptr, &dock_left_id);
				ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_center_id, ImGuiDir_Right, 0.3f, nullptr, &dock_center_id);
				ImGuiID dock_bottom_id = ImGui::DockBuilderSplitNode(dock_center_id, ImGuiDir_Down, 0.4f, nullptr, &dock_center_id);

				ImGui::DockBuilderDockWindow(MLX_UT_ICON_MD_LIST" Tests", dock_left_id);
				ImGui::DockBuilderDockWindow(MLX_UT_ICON_MD_MONITOR" Render", dock_center_id);
				ImGui::DockBuilderDockWindow(MLX_UT_ICON_MD_INFO" About", dock_center_id);
				ImGui::DockBuilderDockWindow(MLX_UT_ICON_MD_SETTINGS" Settings", dock_center_id);
				ImGui::DockBuilderDockWindow(MLX_UT_ICON_MD_TERMINAL" Logs", dock_right_id);
				ImGui::DockBuilderDockWindow(MLX_UT_ICON_MD_RULE" Results", dock_bottom_id);

				ImGui::DockBuilderFinish(dockspace_id);
			}
			ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2{ 0.f, 0.f }, ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_NoWindowMenuButton);
			ImGui::End();
		}

		ImGui::PopStyleVar();
	}
}
