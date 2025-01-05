#include <Graphics/Panels/Logs.h>
#include <Core/MaterialFont.h>
#include <Tests/Tester.h>

namespace mlxut
{
	static std::vector<std::string> Split(const std::string& s, char delim)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> elems;
		while(std::getline(ss, item, delim))
			elems.push_back(std::move(item));
		return elems;
	}

	static bool IsOnlyWhitespaces(const std::string& s)
	{
		return std::all_of(s.begin(), s.end(), isspace);
	}

	LogsPanel::LogsPanel(Tester& tester) : Panel("LogsPanel"), m_tester(tester) {}

	void LogsPanel::OnUpdate(ImVec2 size)
	{
		if(ImGui::Begin(MLX_UT_ICON_MD_TERMINAL" Logs", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			if(ImGui::BeginChild("##mlx_logs", {0.f, 0.f}, ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar))
			{
				auto test = m_tester.GetAllTests()[m_tester.GetSelectedTest()];
				if(test->GetLogs().empty() || IsOnlyWhitespaces(test->GetLogs()))
				{
					ImGui::Dummy(ImVec2(42.0f, (ImGui::GetWindowHeight() - 90.0f) / 2.0f));
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
						ImGui::Indent(((ImGui::GetWindowWidth() - 15.0f) / 2.0f) - ImGui::CalcTextSize("There are no logs").x / 2.0f);
						ImGui::TextUnformatted("There are no logs");
					ImGui::PopStyleColor();
				}
				else
				{
					auto lines = Split(test->GetLogs(), '\n');
					for(std::string& line : lines)
					{
						if(IsOnlyWhitespaces(line))
							continue;

						std::string sub_string;
						ImVec4 print_color = ImGui::GetStyle().Colors[ImGuiCol_Text];
						for(std::size_t i = 0; i <= line.length(); i++)
						{
							if(line[i] == '\033' || i >= line.length())
							{
								if(!sub_string.empty())
								{
									ImGui::PushStyleColor(ImGuiCol_Text, print_color);
										ImGui::TextUnformatted(sub_string.c_str());
									ImGui::PopStyleColor();

									if(i < line.length())
										ImGui::SameLine();
									sub_string.clear();
								}

								if(line.compare(i, 7, "\033[1;34m") == 0)
								{
									print_color = ImVec4(.2f, .5f, 1.f, 1.f);
									i += 7;
								}
								else if(line.compare(i, 7, "\033[1;33m") == 0)
								{
									print_color = ImVec4(1.f, .8f, .0f, 1.f);
									i += 7;
								}
								else if(line.compare(i, 7, "\033[1;35m") == 0)
								{
									print_color = ImVec4(.8f, .2f, .8f, 1.f);
									i += 7;
								}
								else if(line.compare(i, 7, "\033[1;31m") == 0)
								{
									print_color = ImVec4(1.0f, 0.365f, 0.365f, 1.0f);
									i += 7;
								}
								else if(line.compare(i, 6, "\033[1;0m") == 0)
								{
									i += 6;
									print_color = ImGui::GetStyle().Colors[ImGuiCol_Text];
								}
							}
							sub_string.push_back(line[i]);
						}
					}
				}
				ImGui::EndChild();
			}

			ImGui::End();
		}
	}
}
