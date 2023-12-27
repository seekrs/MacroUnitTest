/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_list.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:53:46 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/27 22:23:46 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <material_font.h>
#include <components/tests_list.h>
#include <tests/tester.h>

namespace mlxut
{
	TestList::TestList(Tester* tester) : Panel("test_list"), _tester(tester) {}

	void TestList::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 4, static_cast<float>(size.y) - 21});
		if(!ImGui::Begin("Tests List", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus))
			return;

		if(ImGui::BeginChild("##tests_list_content", {0.f, 0.f}, ImGuiChildFlags_Border))
		{
			const auto& tests = _tester->getAllTests();
			static std::string name;
			name.reserve(128);
			for(int n = 0; n < tests.size(); n++)
			{
				name.clear();
				ImVec4 printColor(1.f, 1.f, 1.f, 1.f);
				if(tests[n]->isPending())
					name += MLXUT_ICON_MD_SCHEDULE" ";
				else if(tests[n]->hasPassed())
				{
					name += MLXUT_ICON_MD_DONE" ";
					printColor = ImVec4(.2f, .8f, 0.1f, 1.f);
				}
				else
				{
					name += MLXUT_ICON_MD_ERROR" ";
					printColor = ImVec4(1.0f, 0.365f, 0.365f, 1.0f);
				}
				name += tests[n]->getName();
				ImGui::PushStyleColor(ImGuiCol_Text, printColor);
					if(ImGui::Selectable(name.c_str(), _tester->getActiveTestIndex() == n))
						_tester->changeActiveTest(n);
				ImGui::PopStyleColor();
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}
}
