#include <Graphics/Panels/Result.h>
#include <Tests/Tester.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	Results::Results(Tester& tester) : Panel("Results"), m_tester(tester) {}

	void Results::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_RULE" Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			auto test = m_tester.GetAllTests()[m_tester.GetSelectedTest()];

			ImGui::Text("Error mean: %f", test->GetMean());

			if(ImGui::BeginChild("ErrorResult", {ImGui::GetWindowWidth() / 2.f - 5.f, 0.f}, ImGuiChildFlags_Border))
			{
				float size_reference = ImGui::GetWindowWidth();
				if(size_reference > ImGui::GetWindowHeight())
					size_reference = ImGui::GetWindowHeight();
				if(size_reference > MLX_WIN_WIDTH)
					size_reference = MLX_WIN_WIDTH;
				ImVec2 size(size_reference - 16.f, size_reference - 16.f);
				ImGui::SetCursorPos({ (ImGui::GetWindowWidth() - size.x) * 0.5f, (ImGui::GetWindowHeight() - size.y) * 0.5f });
				if(test->GetErrorMap() != nullptr)
					ImGui::Image(test->GetErrorMap(), size);
				ImGui::EndChild();
			}

			ImGui::End();
		}
	}
}
