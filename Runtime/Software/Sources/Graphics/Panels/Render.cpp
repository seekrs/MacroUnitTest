#include <Graphics/Panels/Render.h>
#include <Core/MaterialFont.h>
#include <Tests/Tester.h>

namespace mlxut
{
	Render::Render(Tester& tester) : Panel("Render"), m_tester(tester) {}

	void Render::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_MONITOR" Render", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			auto test = m_tester.GetAllTests()[m_tester.GetSelectedTest()];

			ImGui::TextUnformatted(test->GetName().c_str());
			ImGui::SameLine();
			ImGui::TextUnformatted("Result");
			ImGui::SameLine(ImGui::GetWindowWidth() / 2.f + 6.f);
			ImGui::TextUnformatted(test->GetName().c_str());
			ImGui::SameLine();
			ImGui::TextUnformatted("Reference");
			if(ImGui::BeginChild("Result", {ImGui::GetWindowWidth() / 2.f - 5.f, 0.f}, ImGuiChildFlags_Border))
			{
				if(!m_tester.AreTestsRunning())
				{
					float size_reference = ImGui::GetWindowWidth();
					if(size_reference > ImGui::GetWindowHeight())
						size_reference = ImGui::GetWindowHeight();
					if(size_reference > MLX_WIN_WIDTH)
						size_reference = MLX_WIN_WIDTH;
					ImVec2 size(size_reference - 16.f, size_reference - 16.f);
					ImGui::SetCursorPos({ (ImGui::GetWindowWidth() - size.x) * 0.5f, (ImGui::GetWindowHeight() - size.y) * 0.5f });
					ImGui::Image(static_cast<void*>(test->GetResult()), size);
				}
			EndChild:
				ImGui::EndChild();
			}
			ImGui::SameLine();
			if(ImGui::BeginChild("Reference", {ImGui::GetWindowWidth() / 2.f - 5.f - 3.f, 0.f}, ImGuiChildFlags_Border))
			{
				float size_reference = ImGui::GetWindowWidth();
				if(size_reference > ImGui::GetWindowHeight())
					size_reference = ImGui::GetWindowHeight();
				if(size_reference > MLX_WIN_WIDTH)
					size_reference = MLX_WIN_WIDTH;
				ImVec2 size(size_reference - 16.f, size_reference - 16.f);
				ImGui::SetCursorPos({ (ImGui::GetWindowWidth() - size.x) * 0.5f, (ImGui::GetWindowHeight() - size.y) * 0.5f });
				ImGui::Image(static_cast<void*>(test->GetReference()), size);

				ImGui::EndChild();
			}
			ImGui::End();
		}
	}
}
