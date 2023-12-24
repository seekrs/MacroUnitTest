/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_list.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:53:46 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/23 21:25:43 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			for(int n = 0; n < tests.size(); n++)
			{
				if(ImGui::Selectable(tests[n]->getName().c_str(), _tester->getActiveTestIndex() == n))
					_tester->changeActiveTest(n);
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}
}
