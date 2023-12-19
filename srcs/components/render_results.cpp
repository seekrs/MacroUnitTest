/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:26:29 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/19 19:29:57 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/render_results.h>

namespace mlxut
{
	RenderResults::RenderResults() : Panel("render_results") {}

	void RenderResults::onUpdate(ivec2 size)
	{
		ImGui::SetNextWindowPos({static_cast<float>(size.x) / 4 + 1, 20});
		ImGui::SetNextWindowSize({static_cast<float>(size.x) / 2, static_cast<float>(size.y) / 1.5f});
		if(!ImGui::Begin("Render Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
			return;

		ImGui::End();
	}
}
