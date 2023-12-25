/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stats.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:42:16 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/25 15:20:39 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/test_stats.h>

namespace mlxut
{
	TestStats::TestStats() : Panel("test_stats") {}

	void TestStats::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 4.f + 1, static_cast<float>(size.y) / 2.f + 21});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) / 2.f - 22});
		if(!ImGui::Begin("Test Stats", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus))
			return;

		ImGui::End();
	}
}
