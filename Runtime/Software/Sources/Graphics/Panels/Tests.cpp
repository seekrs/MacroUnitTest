#include <Graphics/Panels/Tests.h>
#include <Core/MaterialFont.h>

namespace mlxut
{
	TestsPanel::TestsPanel(Tester& tester) : Panel("TestsPanel"), m_tester(tester) {}

	void TestsPanel::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_LIST" Tests", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			const auto& tests = m_tester.GetAllTests();

			ImGui::Text("All %ld tests", tests.size());
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.2f, .5f, 1.f, 1.f));
				ImGui::Text("%ld pending", m_tester.GetTestsPendingNumber());
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.2f, .8f, .1f, 1.f));
				ImGui::Text("%ld passed", m_tester.GetTestsPassedNumber());
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, .365f, .365f, 1.f));
				ImGui::Text("%ld failed", m_tester.GetTestsFailedNumber());
			ImGui::PopStyleColor();

			if(ImGui::BeginChild("##tests_list_content", {0.f, 0.f}, ImGuiChildFlags_Border))
			{
				static std::string name;
				for(std::size_t n = 0; n < tests.size(); n++)
				{
					name.clear();
					ImVec4 print_color;
					if(tests[n]->HasFailed())
					{
						name += MLX_UT_ICON_MD_ERROR" ";
						print_color = ImVec4(1.f, .365f, .365f, 1.f);
					}
					else if(tests[n]->HasPassed())
					{
						name += MLX_UT_ICON_MD_DONE" ";
						print_color = ImVec4(.2f, .8f, .1f, 1.f);
					}
					else
					{
						name += MLX_UT_ICON_MD_SCHEDULE" ";
						print_color = ImVec4(.2f, .5f, 1.f, 1.f);
					}
					name += tests[n]->GetName();
					ImGui::PushStyleColor(ImGuiCol_Text, print_color);
						if(ImGui::Selectable(name.c_str(), m_tester.GetSelectedTest() == n))
							m_tester.SelectTest(n);
					ImGui::PopStyleColor();
				}
				ImGui::EndChild();
			}

			ImGui::End();
		}
	}
}
