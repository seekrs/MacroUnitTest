#include <Graphics/Panels/Tests.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	TestsPanel::TestsPanel() : Panel("TestsPanel") {}

	void TestsPanel::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_LIST" Tests", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}
	}
}
