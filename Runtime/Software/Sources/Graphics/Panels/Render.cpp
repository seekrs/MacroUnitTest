#include <Graphics/Panels/Render.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	Render::Render() : Panel("Render") {}

	void Render::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_MONITOR" Render", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}
	}
}
