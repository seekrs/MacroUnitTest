#include <Graphics/Panels/Result.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	Results::Results() : Panel("Results") {}

	void Results::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_RULE" Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}
	}
}
