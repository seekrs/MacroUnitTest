/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_list.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:53:46 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 23:29:10 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/tests_list.h>

namespace mlxut
{
	TestList::TestList() : Panel("test_list") {}

	void TestList::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 4, static_cast<float>(size.y) - 21});
		if(!ImGui::Begin("Tests List", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus))
			return;

		ImGui::End();
	}
}
