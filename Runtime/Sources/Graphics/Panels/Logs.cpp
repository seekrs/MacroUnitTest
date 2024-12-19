#include <Graphics/Panels/Logs.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	LogsPanel::LogsPanel() : Panel("LogsPanel") {}

	void LogsPanel::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_TERMINAL" Logs", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}
	}
}
