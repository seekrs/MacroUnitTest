#include <Graphics/Panels/Tests.h>
#include <Core/MaterialFont.h>
#include <Core/Application.h>
#include <Core/OS/OSInstance.h>

namespace mlxut
{
	TestsPanel::TestsPanel(Tester& tester) : Panel("TestsPanel"), m_tester(tester) {}

	void TestsPanel::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_LIST" Tests", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			std::vector<std::shared_ptr<Test>>& tests = m_tester.GetAllTests();

			ImGui::Text("All %ld tests :", tests.size());
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.2f, .5f, 1.f, 1.f));
				ImGui::Text("%ld pending", m_tester.GetTestsPendingNumber());
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.2f, .8f, .1f, 1.f));
				ImGui::Text("%ld passed", m_tester.GetTestsPassedNumber());
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, .8f, .0f, 1.f));
				ImGui::Text("%ld suspicious", m_tester.GetTestsSuspiciousNumber());
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
					else if(tests[n]->IsSuspicious())
					{
						name += MLX_UT_ICON_MD_WARNING" ";
						print_color = ImVec4(1.f, .8f, .0f, 1.f);
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

					if(ImGui::BeginPopupContextItem(nullptr, ImGuiPopupFlags_MouseButtonRight))
					{
						if(ImGui::Button("Run test"))
							m_tester.RunSingleTests(n, Application::Get().GetMLXPath());
						#ifndef MLX_UT_EMBED_TESTS
							if(ImGui::Button("Delete reference"))
								tests[n]->DeleteReference();
							if(ImGui::Button("Delete test"))
							{
								tests[n]->DeleteReference();
								std::filesystem::remove(OSInstance::Get().GetCurrentWorkingDirectoryPath() / "Resources/Tests" / (tests[n]->GetName() + ".lua"));
								tests.erase(tests.begin() + n);
							}
						#endif
						ImGui::EndPopup();
					}
				}
				ImGui::EndChild();
			}

			ImGui::End();
		}
	}
}
