/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_infos.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:33:11 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/28 02:08:19 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/mlx_infos.h>
#include <imgui.h>
#include <tests/tester.h>

namespace mlxut
{
	std::vector<std::string> split(const std::string& s, char delim)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> elems;
		while(std::getline(ss, item, delim))
			elems.push_back(std::move(item));
		return elems;
	}

	bool isWhitespace(const std::string& s)
	{
		return std::all_of(s.begin(), s.end(), isspace);
	}

	MLXinfos::MLXinfos(Tester* tester) : Panel("mlx_infos"), _tester(tester) {}

	void MLXinfos::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 2 + static_cast<float>(size.x) / 4 + 1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 4 - 2, static_cast<float>(size.y) - 21});
		if(!ImGui::Begin("MLX Logs", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus))
			return;

		if(ImGui::BeginChild("##mlx_infos", {0.f, 0.f}, ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar))
		{
			auto& test = _tester->getAllTests()[_tester->getActiveTestIndex()];
			if(test->getMLXinfos().empty() || _tester->testsAreRunning())
			{
				ImGui::Dummy(ImVec2(42.0f, (ImGui::GetWindowHeight() - 90.0f) / 2.0f));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
					ImGui::Indent(((ImGui::GetWindowWidth() - 15.0f) / 2.0f) - ImGui::CalcTextSize("There are no logs").x / 2.0f);
					ImGui::TextUnformatted("There are no logs");
				ImGui::PopStyleColor();
			}
			else
			{
				auto lines = split(test->getMLXinfos(), '\n');
				for(std::string& line : lines)
				{
					if(isWhitespace(line))
						continue;
					ImVec4 printColor(1.f, 1.f, 1.f, 1.f);
					std::size_t pos = 0;
					if((pos = line.find("[1;34m")) != std::string::npos) // messages
					{
						printColor = ImVec4(.2f, .5f, 1.f, 1.f);
						line.erase(0, pos + std::strlen("[1;31m"));
					}
					else if((pos = line.find("[1;35m")) != std::string::npos) // warnings
					{
						printColor = ImVec4(.8f, .2f, .8f, 1.f);
						line.erase(0, pos + std::strlen("[1;31m"));
					}
					else if((pos = line.find("[1;31m")) != std::string::npos) // errors / fatal errors
					{
						printColor = ImVec4(1.0f, 0.365f, 0.365f, 1.0f);
						line.erase(0, pos + std::strlen("[1;31m"));
					}

					pos = line.find("[MacroLibX]");
					if(pos != std::string::npos)
						line.erase(0, pos + std::strlen("[MacroLibX]"));
					pos = line.find(':');
					if(pos != std::string::npos)
						line.erase(pos, std::strlen(":?[1;0m") + 1);

					ImGui::PushStyleColor(ImGuiCol_Text, printColor);
						ImGui::TextUnformatted(line.c_str());
					ImGui::PopStyleColor();
				}
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}
}
