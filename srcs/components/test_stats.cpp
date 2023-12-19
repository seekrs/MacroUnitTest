/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stats.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:42:16 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 20:15:01 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/test_stats.h>

namespace mlxut
{
	TestStats::TestStats() : Panel("test_stats") {}

	void TestStats::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 4 + 1, static_cast<float>(size.y) / 1.5f - 22});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 2, static_cast<float>(size.y) / 3 + 21});
		if(!ImGui::Begin("Test Stats", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
			return;

		ImGui::End();
	}
}