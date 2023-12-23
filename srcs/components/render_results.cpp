/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_results.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:26:29 by maldavid          #+#    #+#             */
/*   Updated: 2023/12/23 00:21:16 by kbz_8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <components/render_results.h>

namespace mlxut
{
	RenderResults::RenderResults() : Panel("render_results") {}

	void RenderResults::onUpdate(ivec2 size)
	{
		if(!ImGui::Begin("Render Results", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
			return;
		ImGui::Text("caca");
		if(!_textures.empty())
			ImGui::Image(static_cast<void*>(_textures[0]), {400, 400});
		ImGui::Text("caca");
		ImGui::End();
	}
}
