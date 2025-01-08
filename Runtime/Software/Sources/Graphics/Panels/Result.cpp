#include <Graphics/Panels/Result.h>
#include <Tests/Tester.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	Results::Results(Tester& tester) : Panel("Results"), m_tester(tester) {}

	void Results::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_RULE" Errors", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			auto test = m_tester.GetAllTests()[m_tester.GetSelectedTest()];

			ImGui::Text("Error mean value: %f", test->GetMean());

			if(ImGui::BeginChild("ErrorResult", { 0.f, 0.f }, ImGuiChildFlags_Border))
			{
				ImGui::TextUnformatted("Error Map:");
				if(test->GetMean() > SUSPICIOUS_THRESHOLD)
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
				}
				else
				{
					ImGui::Dummy(ImVec2(42.0f, (ImGui::GetWindowHeight() - 90.0f) / 2.0f));
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
						ImGui::Indent(((ImGui::GetWindowWidth() - 15.0f) / 2.0f) - ImGui::CalcTextSize("No error map").x / 2.0f);
						ImGui::TextUnformatted("No error map");
					ImGui::PopStyleColor();
				}
				ImGui::EndChild();
			}

			ImGui::End();
		}
	}
}
